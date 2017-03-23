#include "Level1.h"

#include <vector>

#include "../labrat/primitive_shapes/polygon.h"
#include "../labrat/entity/transform.h"
#include "../labrat/scene/camera.h"
#include "../labrat/utilities/units.h"
#include "../labrat/entity/entity.h"
#include "../labrat/graphics/model.h"
#include "../labrat/opengl/vertexdata.h"
#include "../labrat/physics/PhysObj.h"

#include "models/general_models.h"



Level1::Level1()
	: main_camera(Camera( glm::vec3(0.0f, -1.0f, 5.0f)		// Position
						, glm::vec3(0.0, 0.5f, -10.0f)	// Focus
						, glm::vec3(0, 1.0f, 0))		// Up
				)
{
	

	

	background = spawn(spacebackground_model(),
		Transform(glm::vec3(0.0f, 0.0f, background_layer), glm::vec3(10.0f)));


	ground = spawn_body(ground_model(), playable_layer, 0.0f, -1.0f, 20.0f, 1.0f, 0.0f);

	

	for (int i = 0; i < 10; i++)
	{
		trees.push_back(spawn_massless(tree_model(), scenary_layer, -10.0f + i*2.0f, 1.0f, 1.0f, 3.0f));
	}

	flower = spawn_massless(flower_model(), scenary_layer - 0.09f, -2.5f, 0.25f, 1.0f, 1.0f);

	player = spawn_body(player_model(), playable_layer, 0.0f, 3.0f, 1.0f, 1.0f, 2.0f);

	friend_bot1 = spawn_body(friend_model(), playable_layer, 3.0f, 2.0f, 0.5f, 0.5f, 1.0f);

	friend_bot2 = spawn_body(friend_model(), playable_layer, -3.0f, 3.0f, 0.5f,0.5f, 1.0f);
}


Level1::~Level1()
{
}

auto sync_physics_body(Entity* obj) {
	return [obj](auto& level) {
		const float physics_scaling = 1.1f;
		auto& b = obj->body->position;
		glm::vec3 new_pos;
		new_pos[0] = b[0] * physics_scaling;
		new_pos[1] = b[1] * physics_scaling;
		new_pos[2] = 0.0f;
		obj->transform.position = new_pos;
		//std::cout << "Picture is at " << obj->transform.position[0] << " "<< obj->transform.position[1] << "\n";
	};
}

auto camera_track_object(Camera& c, Entity* obj) {
	return [&c, obj](auto& level) {
		c.focus = obj->transform.position;
		c.position[0] = obj->transform.position[0];
		c.position[1] = obj->transform.position[1];
	};
}

auto scale_with_y_position(Entity* affected, Entity* source) {
	return [=](auto& level) {
		auto scaling = abs(source->transform.position[1] + 1.0f);
		//affected->transform.scale[0] = scaling;
		affected->transform.scale[1] = scaling;
	};
}

auto scale_group_with_x_position(std::vector<Entity*>& affected, Entity* source) {
	return[=](auto& level) {
		auto scaling = 2.25f * abs(glm::sin(source->transform.position[0])) + 1.0f;
		for (auto entity : affected) {
			entity->transform.scale[1] = scaling;
			entity->transform.position[1] = scaling - 1.0f;
		}
	};
}

void Level1::construct_updates(vector<update_t<Level1&>>& updates, const vector<SDL_Event>& keyboard_events, const Level1& prev) {
	if (keyboard_events.size() > 0)
		updates.push_back(controls(player, keyboard_events));
	
	// Sync the images with the physics bodies
	updates.push_back(camera_track_object(main_camera, player));
	updates.push_back(sync_physics_body(ground));
	updates.push_back(sync_physics_body(player));
	updates.push_back(sync_physics_body(friend_bot1));
	updates.push_back(sync_physics_body(friend_bot2));

	// Reactive Effects
	updates.push_back(scale_with_y_position(flower, player));
	updates.push_back(scale_group_with_x_position(trees, player));
}