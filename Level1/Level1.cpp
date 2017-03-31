#include "Level1.h"

#include <vector>

#include "../../labrat/primitive_shapes/polygon.h"
#include "../../labrat/entity/transform.h"
#include "../../labrat/scene/camera.h"
#include "../../labrat/utilities/units.h"
#include "../../labrat/entity/entity.h"
#include "../../labrat/graphics/model.h"
#include "../../labrat/opengl/vertexdata.h"
#include "../../labrat/physics/PhysObj.h"

Level1::Level1()
	: game_world(*this)
	, gui(*this)
	, main_camera(Camera(glm::vec3(0.0f, -1.0f, 5.0f)		// Position
		, glm::vec3(0.0, 0.5f, -10.0f)	// Focus
		, glm::vec3(0, 1.0f, 0))		// Up
	) {}

Level1::~Level1()
{
}

auto sync_physics_body(Entity* obj) {
	return [obj](auto& level) {
		//float physics_scaling = 1.1f;
		auto& b = obj->body->position;
		glm::vec3 new_pos;
		new_pos[0] = b[0];
		new_pos[1] = b[1];
		new_pos[2] = 0.0f;
		obj->transform.position = new_pos;
	};
}

auto camera_track_object(Camera& c, Entity* obj) {
	return [&c, obj](auto& level) {
		c.focus = obj->transform.position;
		c.position[0] = obj->transform.position[0];
		c.position[1] = obj->transform.position[1];
	};
}

auto track_object(Entity* o, Entity* other) {
	return [o, other](auto& level) {
		o->transform.position[0] = other->transform.position[0];
		o->transform.position[1] = other->transform.position[1];
	};
}

auto scale_with_y_position(Entity* affected, Entity* source) {
	return [=](auto& level) {
		auto scaling = abs(source->transform.position[1]);
		affected->transform.scale[1] = scaling;
		affected->transform.position[1] = scaling - 0.5f;
	};
}

auto scale_group_with_x_position(std::vector<Entity*>& affected, Entity* source) {
	return[=](auto& level) {
		auto scaling = abs(source->transform.position[0]);
		for (auto entity : affected) {
			entity->transform.scale[1] = scaling;
			entity->transform.position[1] = scaling - 0.5f;
		}
		std::cout << affected[0]->transform.position[1] << std::endl;
	};
}

auto rise_with_x_position(Entity* affected, Entity* source) {
	return[=](auto& level) {
		auto x  = level.game_world.player->transform.position[0];
		auto d = glm::distance(affected->transform.position[0], source->transform.position[0]);
		affected->body->position[1] = (-1.25f * d) - 1.0f;
	};
}

auto be_visible__when_player_on_goal_platform(Entity* sign, Entity* player) {
	return [=](auto& level) {
		if (player->transform.position[0] > 6) {
			sign->transform.position[2] = 1.0f;
		}
	};
}

void Level1::construct_updates(vector<update_t<Level1&>>& updates, const vector<SDL_Event>& keyboard_events, const Level1& prev) {
	if (keyboard_events.size() > 0)
		updates.push_back(controls(game_world.player, keyboard_events));
	
	// Sync the images with the physics bodies
	updates.push_back(camera_track_object(main_camera, game_world.player));
	updates.push_back(track_object(game_world.level_complete_sign, game_world.player));

	// Environment
	updates.push_back(sync_physics_body(game_world.platform1));
	updates.push_back(sync_physics_body(game_world.platform2));
	updates.push_back(sync_physics_body(game_world.rising_platform));

	// Units
	updates.push_back(sync_physics_body(game_world.player));
	updates.push_back(sync_physics_body(game_world.friend_bot1));
	updates.push_back(sync_physics_body(game_world.friend_bot2));

	// Reactive Effects
	updates.push_back(scale_with_y_position(game_world.flower, game_world.player));
	updates.push_back(scale_group_with_x_position(game_world.trees, game_world.player));
	updates.push_back(rise_with_x_position(game_world.rising_platform, game_world.player));
	updates.push_back(be_visible__when_player_on_goal_platform(game_world.level_complete_sign, game_world.player));
}