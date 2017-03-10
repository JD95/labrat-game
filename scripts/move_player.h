#pragma once

#include <vector>

#include "../../labrat/entity/entity.h"
#include "../../labrat/scene/SceneState.h"
#include "../../labrat/scene/camera.h"
#include "../../labrat/scene/scene.h"
#include "../../labrat/reactive/reactive.h"

template <class Level>
struct move_player {

	bool key_hold = false;

	move_player() {}

	void key_down(Entity* player, SDL_Event e) {
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			if (player->body->velocity[1] <= 0)
				player->body->velocity += glm::vec2(0.0f, 5.0f);
			break;

		case  SDLK_a:
			if(!key_hold)
				player->body->velocity += glm::vec2(-2.0f, 0.0f);
			break;

		case SDLK_d:
			if (!key_hold)
				player->body->velocity += glm::vec2(2.0f, 0.0f);
			break;

		default: break;
		}

		key_hold = true;
	}

	void key_up(Entity* player, SDL_Event e) {
		switch (e.key.keysym.sym)
		{
		case  SDLK_a:
			player->body->velocity -= glm::vec2(-2.0f, 0.0f);
			break;

		case SDLK_d:
			player->body->velocity -= glm::vec2(2.0f, 0.0f);
			break;

		default: break;
		}

		key_hold = false;
	}

	update_t<Level&> operator()(Entity* player, std::vector<SDL_Event> events) {
		return[this, player, events](auto& l) {
			// Negative because we are moving the world not the camera
			const float camera_speed = 0.05f;

			for (auto& e : events) {
				if (e.type == SDL_KEYDOWN) {
					key_down(player, e);
				}
				else {
					key_up(player, e);
				}
			}
		};
	}
};