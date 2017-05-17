#pragma once

#include <vector>
#include <functional>

#include "../../labrat/entity/entity.h"
#include "../../labrat/scene/SceneState.h"
#include "../../labrat/scene/camera.h"
#include "../../labrat/scene/scene.h"
#include "../../labrat/reactive/reactive.h"

#include "../../labrat/sound/Sound.h"
#include "../scripts/VoiceClips.h"
#include "../models/general_models.h"
#include "../../labrat/scene/Layers.h"
#include <glm.hpp>

#include <SDL_mixer.h>

using im_done = std::function<glm::vec3(std::vector<SDL_Event>, bool, glm::vec3)>;

struct VolumeSlides {
	Sound* music;
	VoiceClips* audio_tracks;
	SoundClips<7>* landing_sounds;
	SoundClips<3>* bounce_sounds;
	Reactive<float> music_percent;
	Reactive<float> sfx_percent;

	VolumeSlides(Sound* m, VoiceClips* a, SoundClips<7>* p, SoundClips<3>* b)
		: music_percent(1.0f)
		, sfx_percent(1.0f)
		, music(m)
		, audio_tracks(a)
		, landing_sounds(p)
		, bounce_sounds(b)
	{}

	glm::vec3 operator()(std::vector<SDL_Event> events, bool toggled, glm::vec3 position) {
		if (toggled) {

			float y_offset = position[1] == 0.0f ? 0.0f : 100.0f;

			for (auto event : events) {
				bool within_x = event.button.x > 360 && event.button.x < 770;
				bool within_y = event.button.y > 345 + y_offset && event.button.y < 365 + y_offset;
				if (event.type == SDL_MOUSEBUTTONDOWN && within_x && within_y) {
					position[0] = (event.button.x * 0.00185185f) - 1.0f;
					if (position[1] == 0.0f) {
						sfx_percent.v = (event.button.x - 360.0f) / (float)410;
						for (auto c : audio_tracks->intro_clips.v) {
							c->audio->volume = (int)(sfx_percent.v * 128);
						}
						for (auto c : audio_tracks->malaphor_clips.v) {
							c->audio->volume = (int)(sfx_percent.v * 128);
						}
						for (auto c : audio_tracks->witty_clips.v) {
							c->audio->volume = (int)(sfx_percent.v * 128);
						}
						for (auto c : *landing_sounds) {
							c->audio->volume = (int)(sfx_percent.v * 128);
						}
						for (auto c : *bounce_sounds) {
							c->audio->volume = (int)(sfx_percent.v * 128);
						}
					}
					else {

						music_percent.v = (event.button.x - 360.0f) / (float)410;
						//std::cout << music_percent.value << "\n";
						music->audio->volume = (int)(music_percent.v * 128);
					}
					return position;
				}
			}
		}

		return position;
	}
};

class GUI
{
	SceneState& level;

	int current_hp;
	float hp_x_position, hp_y_position;
	std::vector<Entity*> hp_bar;

public:
	Reactive<bool> settings_active;
	GUI(SceneState& state, Sound* m, VoiceClips* a, SoundClips<7>* p, SoundClips<3>* b);
	~GUI();
	Entity* settings_shortcut;
	Entity* music_slider;
	Entity* sfx_slider;
	Entity* settings_window;
	VolumeSlides slide_script;
	void lose_hp();

	// And now the tricky part...
	auto make_toggle_settings(im_done f) {
		return [f](std::vector<SDL_Event> events, bool toggle, glm::vec3 position)
		{
			for (auto event : events) {
				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.x < 40 && event.button.y < 40) {
					if (toggle) position.x += 10.0f;
					else position.x -= 10.0f;
				}
			}
			return f(events, toggle, position);
		};
	}

};

bool switch_toggle(std::vector<SDL_Event> events, bool toogle);