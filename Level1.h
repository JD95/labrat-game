#pragma once

#include <SDL.h>
#include <vector>

#include "../labrat/entity/entity.h"
#include "../labrat/scene/SceneState.h"
#include "../labrat/scene/camera.h"
#include "../labrat/scene/scene.h"
#include "../labrat/reactive/reactive.h"
#include "scripts/move_player.h"


const float background_layer = -0.1f;
const float scenary_layer = -0.09f;
const float playable_layer = 0.0f;

struct Level1 : public SceneState
{
	Reactive<Camera> main_camera;

	// Platforms
	Entity* rising_platform;
	Entity* start_wall;
	Entity* platform1;
	Entity* platform2;

	// Units
	Entity* friend_bot1;
	Entity* friend_bot2;
	Entity* player;

	// props
	std::vector<Entity*> trees;
	Entity* background;
	Entity* flower;
	Entity* goal_sign;
	Entity* level_complete_sign;

	// stateful updates
	move_player<Level1> controls;

	Level1();
	~Level1();
	void construct_updates(
		vector<update_t<Level1&>>& updates, 
		const vector<SDL_Event>& keyboard_events, 
		const Level1& prev);
};


