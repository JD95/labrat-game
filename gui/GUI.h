#pragma once
#include "../../labrat/entity/entity.h"
#include "../../labrat/scene/SceneState.h"
#include "../../labrat/scene/camera.h"
#include "../../labrat/scene/scene.h"
#include "../../labrat/reactive/reactive.h"

#include "../models/general_models.h"
#include "../../labrat/scene/Layers.h"

class GUI
{
	int current_hp;
	float hp_x_position, hp_y_position;
	std::vector<Entity*> hp_bar;
	

public:
	GUI(SceneState& state);
	~GUI();
};

