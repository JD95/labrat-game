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

constexpr float model_body_ratio = 1.0f;

constexpr glm::vec3 physics_ratio_scaling(float x, float y) {
	return glm::vec3(model_body_ratio * x, model_body_ratio * y, 1.0f);
}

Level1::Level1()
	: main_camera(Camera( glm::vec3(0.0f, -1.0f, 10.0f)		// Position
						, glm::vec3(0.0, 0.5f, -10.0f)	// Focus
						, glm::vec3(0, 1.0f, 0))		// Up
				)
{
	

	float world_step = 0.0167f;

	picture1 = spawn(ground_model(), 
		Transform(glm::vec3(0, 0.0f, 0), physics_ratio_scaling(5.0f, 1.0f)),
		PhysObj (0.0, -1.0, 0.0f, 1.0, 10.0, world_step));

	picture1->body->dynamic_friction = 0.30f;
	picture1->body->static_friction = 0.35f;

	player = spawn(player_model(),
		Transform (glm::vec3(0, 2.0f, 0), physics_ratio_scaling(1.0f, 1.0f)),
		PhysObj(0.0, 3.0, 2.0, 1.0, 1.0, world_step));

	friend_bot1 = spawn(friend_model(),
		Transform(glm::vec3(3.0f, 2.0f, 0.0f), physics_ratio_scaling(0.5f, 0.5f)),
		PhysObj(3.0f, 2.0f, 1.0f, 0.5, 0.5, world_step));

	friend_bot2 = spawn(friend_model(),
		Transform(glm::vec3(-3.0f, 3.0f, 0.0f), physics_ratio_scaling(0.5f, 0.5f)),
		PhysObj(-3.0f, 3.0f, 1.0f, 0.5, 0.5, world_step));
}


Level1::~Level1()
{
}

update_t<Level1&> sync_physics_body(Entity* obj) {
	return [obj](auto& level) {
		auto& b = obj->body->position;
		glm::vec3 new_pos;
		new_pos[0] = b[0];
		new_pos[1] = b[1];
		new_pos[2] = 0.0f;
		obj->transform.position = new_pos;
		//std::cout << "Picture is at " << obj->transform.position[0] << " "<< obj->transform.position[1] << "\n";
	};
}

update_t<Level1&> camera_track_object(Camera& c, Entity* obj) {
	return [&c, obj](auto& level) {
		c.focus = obj->transform.position;
		c.position[0] = obj->transform.position[0];
		c.position[1] = obj->transform.position[1];
	};
}

void Level1::construct_updates(vector<update_t<Level1&>>& updates, const vector<SDL_Event>& keyboard_events, const Level1& prev) {
	if (keyboard_events.size() > 0)
		updates.push_back(controls(player, keyboard_events));
	
	// Sync the images with the physics bodies
	updates.push_back(camera_track_object(main_camera, player));
	updates.push_back(sync_physics_body(picture1));
	updates.push_back(sync_physics_body(player));
	updates.push_back(sync_physics_body(friend_bot1));
	updates.push_back(sync_physics_body(friend_bot2));
}