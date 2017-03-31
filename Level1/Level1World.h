#pragma once

#include "../../labrat/entity/entity.h"
#include "../../labrat/scene/SceneState.h"
#include "../../labrat/scene/camera.h"
#include "../../labrat/scene/scene.h"
#include "../../labrat/reactive/reactive.h"
#include "../scripts/move_player.h"
#include "../models/general_models.h"

#include "../../labrat/scene/Layers.h"

struct Level1World
{
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

	Level1World(SceneState& state)
	{
		// Props
		background = state.spawn(spacebackground_model(),
			Transform(glm::vec3(0.0f, 0.0f, background_layer), glm::vec3(10.0f)));

		for (int i = 0; i < 3; i++)
			trees.push_back(state.spawn_massless(tree_model(), scenary_layer, -2.25f + i*1.5f, 0.0f, 1.0f, 1.0f));

		flower = state.spawn_massless(flower_model(), scenary_layer + 0.1f, -2.5f, 0.0f, 1.0f, 1.0f);
		goal_sign = state.spawn_massless(goal_sign_model(), scenary_layer, 2.0, -0.5, 3.0f, 3.0f);


		// Platforms 
		platform1 = state.spawn_body(ground_model(), playable_layer, 0.0f, -1.0f, 5.0f, 1.0f, 0.0f);
		rising_platform = state.spawn_body(ground_model(), playable_layer, 4.0f, -1.0f, 2.0f, 1.0f, 0.0f);
		platform2 = state.spawn_body(ground_model(), playable_layer, 8.0f, -1.0f, 5.0f, 1.0f, 0.0f);


		// Units
		player = state.spawn_body(player_model(), playable_layer, 0.0f, 3.0f, 1.0f, 1.0f, 2.0f);
		friend_bot1 = state.spawn_body(friend_model(), playable_layer, 3.5f, 2.0f, 0.5f, 0.5f, 1.0f);
		friend_bot2 = state.spawn_body(friend_model(), playable_layer, -3.0f, 3.0f, 0.5f, 0.5f, 1.0f);

		level_complete_sign = state.spawn_massless(levelcomplete_model(), -10.0f, 0.0f, 0.0f, 5.0f, 5.0f);
	}

public:
	Level1World();
	~Level1World();
};

