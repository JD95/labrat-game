#include "GUI.h"

#include "../scripts/VoiceClips.h"

GUI::GUI(SceneState & state, Sound* m, VoiceClips* a, SoundClips<7>* p, SoundClips<3>* b)
	: level(state)
	, slide_script(m, a, p, b)
{	
	// Mouse Interface
	settings_active = false;
	settings_shortcut = state.gui_spawn(settings_shortcut_model(), -0.96f, 0.95f, 0.03f, 0.04f);
	settings_window = state.gui_spawn(settings_model(), 10.0f, 0.0f, 0.5f, 0.5f);
	music_slider = state.gui_spawn(slider_model(), 10.40f, 0.0f, 0.015f, 0.05f);
	music_slider->transform.position.v[2] -= 0.1f;
	sfx_slider = state.gui_spawn(slider_model(), 10.40f, -0.28f, 0.015f, 0.05f);
	sfx_slider->transform.position.v[2] -= 0.1f;
	
	// HP Bar (Entities created after this will be deleted when health is lost)
	current_hp = 24;
	hp_x_position = -0.3f;
	hp_y_position = 0.95f;

	for (int i = 0; i < current_hp; i++) {
		hp_bar.push_back(state.gui_spawn(hp_segment_model(), hp_x_position + (i * 0.025f), hp_y_position, 0.01f, 0.03f));
	}
}

GUI::~GUI()
{
}

void GUI::lose_hp()
{
	current_hp--;
	if (current_hp >= 0) {
		level.gui_entities.destroy_object(hp_bar[current_hp]->id);
	}
}



bool switch_toggle(std::vector<SDL_Event> events, bool toogle)
{
	for (auto event : events) {
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.x < 40 && event.button.y < 40) {
			return !toogle;
		}
	}
	return toogle;
}
