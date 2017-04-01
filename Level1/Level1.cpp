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
		, glm::vec3(0.0, 0.5f, -10.0f)	// Focus
		, glm::vec3(0, 1.0f, 0));		// Up
}

Level1::~Level1()
{
}

auto sync_physics_body(Entity* obj) {
	return from(obj->body)
		.use([](PhysObj* b) { return glm::vec3(b->position[0],b->position[1],0.0f); })
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

//auto track_object(Transform o, Transform other) {
//	o.position[0] = other.position[0];
//	o.position[1] = other.position[1];
//	return o;
//}

//auto scale_with_y_position(Transform affected, Transform source) {
//	auto scaling = abs(source.position[1]);
//	affected.scale[1] = scaling;
//	affected.position[1] = scaling - 0.5f;
//	return affected;
//}

// TODO: Group transforms
//auto scale_group_with_x_position(std::vector<Entity*> affected, Entity* source) {
//	auto scaling = abs(source->transform.position[0]);
//	for (auto entity : affected) {
//		entity->transform.scale[1] = scaling;
//		entity->transform.position[1] = scaling - 0.5f;
//	}
//
//	return affected;
//}

//auto rise_with_x_position(PhysObj* affected, PhysObj* source) {
//	auto d = glm::distance(affected->position[0], source->position[0]);
//	affected->position[1] = (-1.25f * d) - 1.0f;
//	return affected;
//}
//
//auto be_visible__when_player_on_goal_platform(Transform sign, Transform player) {
//	if (player.position[0] > 6) {
//		sign.position[2] = 1.0f;
//	}
//	return sign;
//}

void Level1::construct_updates(vector<std::unique_ptr<Updater>>& updates) {

	// Physics syncing
	updates.push_back(sync_physics_body(game_world.platform1));
	updates.push_back(sync_physics_body(game_world.player));
	updates.push_back(sync_physics_body(game_world.friend_bot1));
	updates.push_back(sync_physics_body(game_world.friend_bot2));

	updates.push_back(camera_track_object(main_camera, game_world.player));
	updates.push_back(controls(game_world.player, keyboard_events));
}