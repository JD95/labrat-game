#pragma once

#include "../../labrat/sound/Sound.h"
#include <array>
#include "../../labrat/reactive/reactive.h"
#include "../../labrat/scene/SceneState.h"

struct Level1Sounds
{
	Reactive<Sound*> music;
	Reactive<std::array<Sound*, 7>> pearson_landing_sounds;
	Reactive<std::array<Sound*, 3>> monster_bounces;
	Level1Sounds(SceneState& scene);
	~Level1Sounds();
};

