#pragma once

#include "../../labrat/sound/Sound.h"
#include <array>
#include "../../labrat/reactive/reactive.h"
#include "../../labrat/scene/SceneState.h"

struct Level1Sounds
{
	Reactive<Sound*> music;
	Reactive<SoundClips<7>> pearson_landing_sounds;
	Reactive<SoundClips<3>> monster_bounces;
	Reactive<SoundClips<2>> intro_clips;
	Reactive<SoundClips<11>> malaphors;
	Reactive<SoundClips<33>> witty;

	Level1Sounds(SceneState& scene);
	~Level1Sounds();
};

