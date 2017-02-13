#pragma once

#include "../labrat/entity/entity.h"
#include "../labrat/scene/SceneState.h"
#include "../labrat/scene/camera.h"
#include "../labrat/scene/scene.h"

struct Level1 : public SceneState
{
	Camera main_camera;
	Entity* picture1;
	Entity* picture2;

	Level1();
	~Level1();
};

void game_updates(vector<update_t<Level1&>>& updates, const Level1& prev);
