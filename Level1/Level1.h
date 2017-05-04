#pragma once

#include <SDL.h>
#include <vector>
#include <memory>

#include "../../labrat/entity/entity.h"
#include "../../labrat/scene/SceneState.h"
#include "../../labrat/scene/camera.h"
#include "../../labrat/scene/scene.h"
#include "../../labrat/reactive/reactive.h"
#include "../../labrat/scene/Layers.h"

#include "../scripts/move_player.h"
#include "../models/general_models.h"
#include "../Level1/Level1World.h"
#include "../gui/GUI.h"
#include "../Level1/Level1Sounds.h"

struct Level1 : public SceneState
{
	Level1World game_world;
	Level1Sounds game_sounds;
	GUI gui;

	// stateful updates
	move_player controls;

	Level1();
	~Level1();
	void construct_updates(vector<std::unique_ptr<Updater>>& updates);
};


