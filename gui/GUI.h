#pragma once

#include <vector>
#include <functional>

#include "../../labrat/entity/entity.h"
#include "../../labrat/scene/SceneState.h"
#include "../../labrat/scene/camera.h"
#include "../../labrat/scene/scene.h"
#include "../../labrat/reactive/reactive.h"

#include "../models/general_models.h"
#include "../../labrat/scene/Layers.h"
#include <glm.hpp>
using im_done = std::function<glm::vec3(std::vector<SDL_Event>, bool, glm::vec3)>;
class GUI
{
	SceneState& level;

	int current_hp;
	float hp_x_position, hp_y_position;
	std::vector<Entity*> hp_bar;

public:
	Reactive<bool> settings_active;
	GUI(SceneState& state);
	~GUI();
	Entity* settings_shortcut;
	Entity* music_slider;
	Entity* sfx_slider;
	Entity* settings_window;
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


glm::vec3 slide_handle(std::vector<SDL_Event> events, bool toggled, glm::vec3 position);

bool switch_toggle(std::vector<SDL_Event> events, bool toogle);