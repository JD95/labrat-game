#include "Level1Sounds.h"



Level1Sounds::Level1Sounds(SceneState& scene)
{
	music.value = scene.load_sound("labrat-game/assets/music/pearson_awakes.wav");
	music.value->play();

	pearson_landing_sounds.value[0] = scene.load_sound("labrat-game/assets/sound_effects/pearson_step_ asharp.wav");
}


Level1Sounds::~Level1Sounds()
{
}
