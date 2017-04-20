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
{
	main_camera = Camera(glm::vec3(0.0f, -1.0f, 5.0f)		// Position
		, glm::vec3(0.0, 0.5f, -20.0f)	// Focus
		, glm::vec3(0, 1.0f, 0));		// Up
}

Level1::~Level1()
{
}

auto sync_physics_body(Entity* obj) {
	return from(obj->body)
		.use([](PhysObj* b) { 

			if (b->shape.type == 1) {
				auto shape = b->shape.get_coll().Rect;
				// Adjusting the model to the "center" of the shape
				auto x = b->position[0];// +(0.5f * shape.width);
				auto y = b->position[1];// +(0.5f * shape.height);
				
				//if (x < 0) std::cout << "PASSED THE ORIGIN!!!\n";

				return glm::vec3(x, y, 0.0f);
			}

			return glm::vec3(b->position[0], b->position[1], 0.0f);
			
		})
		.determine(obj->transform.position);
}

auto camera_track_object(Reactive<Camera>& camera, Entity* object) {
	return from(camera, object->transform.position)
		// Ignore this error, its a false positive
		.use([](Camera c, glm::vec3 position) {
			c.focus = position;
			c.position[0] = position[0];
			c.position[1] = position[1];
			return c; })
		.determine(camera);
}

auto track_object_xy(Entity* tracker, Entity* source) {
	auto tracker_z = tracker->transform.position.value[2];
	return from(source->transform.position)
		.use([tracker_z](glm::vec3 p) { return glm::vec3(p[0], p[1], tracker_z); })
		.determine(tracker->transform.position);
}


auto rise_with_x_position(Entity* affected, Entity* source) {

	auto original_position = affected->body.value->position[1];

	return from(affected->body, source->body)
		.use([original_position](PhysObj* a, PhysObj* s) {
		
			if (s->position[0] < a->position[0]) {
				auto d = glm::distance(a->position[0], s->position[0]);
				a->position[1] = original_position + (-1.0f * d);
			}
			return a; })
		.determine(affected->body);
}

auto respawn_player(Entity* player, GUI& gui) {

	auto original_position = player->transform.position.value;

	return from(player->body)
		.use([original_position, &gui](PhysObj* body) {
			if (body->position[0] > 20.0f && body->position[1] < 3.0f) {
				gui.lose_hp();
				body->position = original_position;
			}
			return body; })
		.determine(player->body);
}

auto animate(Reactive<Int64>& time, Entity* entity) {
	auto sprite_box = entity->model->sprite_box;
	return from(time, entity->model->sprite_position)
		.use([sprite_box](Int64 t, glm::vec2 p) {
			//std::cout << t << "\n";
		const float x_step = 42.0f / 256.0f;
		const float y_step = 52.0f / 256.0f;
			if (t % 15 == 0) {
				std::cout << p[0] << ", " << p[1] << "\n";
				//std::cout << "Animation step!\n";
				p[0] += x_step;
				if (p[0] > 5.0f * x_step) {
					p[0] = 0.0f;
					p[1] -= y_step;
				}
				if (p[1] < -y_step) {
					p[1] = 1.0f - (y_step);
				}
					
			}
			return p; })
		.determine(entity->model->sprite_position);
}

void Level1::construct_updates(vector<std::unique_ptr<Updater>>& updates) {
	glm::vec2 grav_normal = get_grav_norm();

	// Physics syncing
	for (auto platform : game_world.platforms)
		updates.push_back(sync_physics_body(platform));

	updates.push_back(sync_physics_body(game_world.player));

	for (auto platform : game_world.rising_platforms) {
		updates.push_back(sync_physics_body(platform));
		updates.push_back(rise_with_x_position(platform, game_world.player));
	}

	updates.push_back(camera_track_object(main_camera, game_world.player));
	updates.push_back(controls(game_world.player, keyboard_events, grav_normal));

	

	updates.push_back(track_object_xy(game_world.background, game_world.player));
	updates.push_back(respawn_player(game_world.player, gui));

	updates.push_back(animate(time, game_world.player));
}