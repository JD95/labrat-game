#pragma once

#include <vector>

#include "../../labrat/entity/entity.h"
#include "../../labrat/scene/SceneState.h"
#include "../../labrat/scene/camera.h"
#include "../../labrat/scene/scene.h"
#include "../../labrat/reactive/reactive.h"
#include "../scripts/move_player.h"
#include "../models/general_models.h"

#include "../../labrat/scene/Layers.h"
#include "../../labrat/reactive/reactive.h"
#include "../units/Player.h"

struct Level1World
{
	// Platforms
	std::vector<Entity*> rising_platforms;
	std::vector<Entity*> platforms;

	// Units
	Entity* friend_bot1;
	Entity* friend_bot2;
	Player player;

	Entity* enemy;

	// props
	//std::vector<Entity*> trees;
	Entity* background;
	Entity* lava;
	//Entity* flower;
	Entity* goal_sign;
	Entity* level_complete_sign;

	Level1World(SceneState& state);
	~Level1World();
};

