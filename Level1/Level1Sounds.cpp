#include "Level1Sounds.h"
#include <filesystem>


Level1Sounds::Level1Sounds(SceneState& scene)
{
	music.value = scene.load_sound("labrat-game/assets/music/pearson_awakes.wav");
	music.value->play();

	std::string path = "labrat-game/assets/sound_effects/";
	std::string steps[7] = {
		"pearson_step_ fsharp_low.wav",
		"pearson_step_ gsharp.wav",
		"pearson_step_ asharp.wav",
		"pearson_step_ c.wav",
		"pearson_step_ d.wav",
		"pearson_step_ e.wav",
		"pearson_step_ fsharp_high.wav"
	};
	for (size_t i = 0; i < pearson_landing_sounds.value.size(); i++){
		pearson_landing_sounds.value[i] = scene.load_sound(path + steps[i]);
	}
	
	std::string bounces[7] = {
		"bounce_low.wav",
		"bounce_mid.wav",
		"bounce_high.wav"
	};
	for (size_t i = 0; i < monster_bounces.value.size(); i++) {
		monster_bounces.value[i] = scene.load_sound(path + "monster/"+ bounces[i]);
	}

	for (size_t i = 0; i < intro_clips.value.size(); i++)
	{
		intro_clips.value[i] = scene.load_sound(path + "ai/intro/intro-" + std::to_string(i+1) + ".wav");
	}

	for (size_t i = 0; i < malaphors.value.size(); i++)
	{
		malaphors.value[i] = scene.load_sound(path + "ai/malaphor/malaphor-" + std::to_string(i+1) + ".wav");
	}

	for (size_t i = 0; i < witty.value.size(); i++)
	{
		witty.value[i] = scene.load_sound(path + "ai/witty/witty-" + std::to_string(i+1) + ".wav");
	}
}


Level1Sounds::~Level1Sounds()
{
}
