#include "Level1.h"

#include <vector>
#include <array>

#include "../../labrat/primitive_shapes/polygon.h"
#include "../../labrat/entity/transform.h"
#include "../../labrat/scene/camera.h"
#include "../../labrat/utilities/units.h"
#include "../../labrat/entity/entity.h"
#include "../../labrat/graphics/model.h"
#include "../../labrat/opengl/vertexdata.h"
#include "../../labrat/physics/PhysObj.h"
#include "../../labrat/texture/SpriteSheet.h"
#include "../../labrat//sound/Sound.h"


Level1::Level1()
	: game_world(*this)
	, game_sounds(*this)
	, gui(*this, game_sounds.music.value, &voice, &game_sounds.pearson_landing_sounds.value, &game_sounds.monster_bounces.value)
	, voice(game_sounds.intro_clips, game_sounds.malaphors, game_sounds.witty)
{
	main_camera = Camera(glm::vec3(0.0f, -1.0f, 5.0f)		// Position
		, glm::vec3(0.0, 0.5f, -20.0f)	// Focus
		, glm::vec3(0, 1.0f, 0));		// Up
}

Level1::~Level1()
{
}

auto sync_physics_body(Entity* obj) {
	return from(obj->body)
		.use([](PhysObj* b) { 

			if (b->shape.type == 1) {
				auto shape = b->shape.get_coll().Rect;
				// Adjusting the model to the "center" of the shape
				auto x = b->position[0];// +(0.5f * shape.width);
				auto y = b->position[1];// +(0.5f * shape.height);
				
				//if (x < 0) std::cout << "PASSED THE ORIGIN!!!\n";

				return glm::vec3(x, y, 0.0f);
			}

			return glm::vec3(b->position[0], b->position[1], 0.0f);
			
		})
		.determine(obj->transform.position);
}

auto camera_track_object(Reactive<Camera>& camera, Entity* object) {
	return from(camera, object->transform.position)
		// Ignore this error, its a false positive
		.use([](Camera c, glm::vec3 position) {
			c.focus = position;
			c.position[0] = position[0];
			c.position[1] = position[1];
			return c; })
		.determine(camera);
}

auto track_object_xy(Entity* tracker, Entity* source) {
	auto tracker_z = tracker->transform.position.value[2];
	return from(source->transform.position)
		.use([tracker_z](glm::vec3 p) { return glm::vec3(p[0], p[1], tracker_z); })
		.determine(tracker->transform.position);
}


auto rise_with_x_position(Entity* affected, Entity* source) {

	auto original_position = affected->body.value->position[1];

	return from(affected->body, source->body)
		.use([original_position](PhysObj* a, PhysObj* s) {
		
			if (s->position[0] < a->position[0]) {
				auto d = glm::distance(a->position[0], s->position[0]);
				a->position[1] = original_position + (-1.0f * d);
			}
			return a; })
		.determine(affected->body);
}

auto respawn_player(Entity* player, GUI& gui) {

	auto original_position = player->transform.position.value;

	return from(player->body)
		.use([original_position, &gui](PhysObj* body) {
			if (body->position[0] > 20.0f && body->position[1] < 3.0f) {
				gui.lose_hp();
				body->position = original_position;
			}
			return body; })
		.determine(player->body);
}

auto animate(Reactive<Int64>& time, Entity* entity, int update_rate) {
	
	return from(time, entity->model->sprite_position)
		.use([entity, update_rate] (Int64 t, glm::vec2 p) mutable {
			return (t % update_rate == 0) ? entity->model->sprite_sheet.step_animation() : p; })
		.determine(entity->model->sprite_position);
}

auto sync_player_animation(Reactive<std::vector<SDL_Event>>& events, Entity* player) {
	bool facing_right = true;
	return from(events, player->body, player->model->sprite_sheet.current_animation)
		.use([right = facing_right] (std::vector<SDL_Event> events, PhysObj* body, unsigned int c) mutable {

			for (auto e : events) {

				if (e.key.keysym.sym == SDLK_d) {
					right = true;
					return 3u;
				}
				else if (e.key.keysym.sym == SDLK_a) {
					right = false;
					return 4u;
				}
				else if (e.key.keysym.sym == SDLK_SPACE) return right ? 5u : 6u;
			}

			if (body->velocity[0] > -0.1 && body->velocity[0] < 0.01)
				return right ? 1u : 2u;




			return c; })
		.determine(player->model->sprite_sheet.current_animation);
}

auto player_health(Player& p, Entity* enemy, GUI& gui) {
	return from(p.health, p.entity->body)
		.use([&gui, e = enemy->id](int hp, PhysObj* body) {
			for (auto& info : body->collisions.contact()) {
				if (info.id == e) {
					gui.lose_hp();
					gui.lose_hp();
					gui.lose_hp();
					return hp - 3;
				}
			}
			return hp; })
		.determine(p.health);
}

auto player_damage_knockback(Player& p, Entity* enemy) {
	return from(p.entity->body, enemy->body)
		.use([](PhysObj* player, PhysObj* enemy) {
			for (auto& info : player->collisions.enter) {
				if (info.id == enemy->entity_ID) {
					auto force_direction = (player->position - enemy->position);
					auto applied_force = 5.0f * glm::normalize(force_direction)[0];
					player->velocity[0] += applied_force;
				}
			}

			return player; })
		.determine(p.entity->body);
}

auto bounce(Entity* entity, Entity* source) {
	return from(entity->body, source->body)
		.use([](PhysObj* body, PhysObj* s) {
		if (glm::distance(body->position, s->position) < 5.0f) {
			for (auto& c : body->collisions.enter) {
				if (c.velocity[1] > 0.5f) {
					body->velocity[1] += 4;
					break;
				}
			}
		}
		return body;
	}).determine(entity->body);
}

auto enemy_persue_player(PhysObj* enemy, PhysObj* player) {

	const float speed_c = 1.0f;
	const float trigger_distance = 5.0f;
	auto distance = glm::distance(enemy->position, player->position);

	if (distance < trigger_distance) {
		auto player_direction = glm::normalize(player->position - enemy->position);
		enemy->velocity[0] = ((1.0f / distance) * speed_c) * player_direction[0];
	}

	return enemy;
}

auto click_event_handler(std::vector<SDL_Event> events, glm::vec3 position) {
	for (auto event : events) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			position.x = (float(event.button.x) - 540.0f) / 540.0f;
			position.y = -(float(event.button.y) - 360.0f) / 360.0f;
		}
	}
	return position; 
}

auto raise_if_past(Entity* block, Player& player) {
	return from(block->body, player.entity->body)
		.use([](PhysObj* b, PhysObj* p) {
			if (p->position[0] > 45.0f) {
				if (b->position[1] < 5.0f) {
					b->position[1] += 0.1f;
				}
			}
			return b;
	}).determine(block->body);
}

auto mouse_click_update(Reactive<std::vector<SDL_Event>>& events, Entity* elm) {
	return from(events, elm->transform.position)
		.use(click_event_handler)
		.determine(elm->transform.position);
}


auto end_game(Player& player, Reactive<int>& current_level, object_id win_block) {
	return from(player.entity->body, player.health, current_level)
		.use([win_block](PhysObj* body, int hp, int level) {
		if (hp <= 0)
			return -1;
		else {
			for (auto c : body->collisions.enter) {
				if (c.id == win_block) return 2;
				else return level;
			}
		}
	}).determine(current_level);
}

template <int n>
auto landing_sound(Entity* player, Reactive<SoundClips<n>>& sounds) {
	return from(player->body, sounds)
		.use([](PhysObj* body, SoundClips<n> steps) {
			for (auto c : body->collisions.enter) {
				if (c.velocity[1] > 0.5f) {
					steps[rand() % n]->play();
					break;
				}
			}
			return body;
		}).determine(player->body);
}



auto raise_two_blocks(Entity* a, Player& p) {
	float starting_y = a->body.value->position[1];
	return from(a->body, p.entity->body)
		.use([y = starting_y](PhysObj* block, PhysObj* player) {
		if (player->position[0] >= block->position[0]) {
			return block;
		}
		else {
			auto d = 1.0f/glm::distance(block->position[0], player->position[0]);
			auto cap = player->position[1] > 6.0f ? y + 1 : y;
			block->position[1] = cap - ((0.5f*d) > 2.0f ? 1.0f : (0.5f*d));
			return block;
		}

	}).determine(a->body);
}

auto move_right(Entity* a, Player& p) {
	return from(a->body, p.entity->body)
		.use([](PhysObj* b, PhysObj* p) {
			if (p->position[1] > 6.0f) {
				if (b->position[0] < 49.0f) {
					b->position[0] += 0.1f;
				}
			}
			return b;
	}).determine(a->body);
}

void Level1::construct_updates(vector<std::unique_ptr<Updater>>& updates) {
	glm::vec2 grav_normal = get_grav_norm();

	// Physics syncing
	for (auto platform : game_world.platforms)
		updates.push_back(sync_physics_body(platform));

	updates.push_back(sync_physics_body(game_world.player.entity));
	updates.push_back(sync_physics_body(game_world.enemy));

	for (auto platform : game_world.rising_platforms) {
		updates.push_back(sync_physics_body(platform));
		updates.push_back(rise_with_x_position(platform, game_world.player.entity));
	}

	updates.push_back(sync_physics_body(game_world.puzzle1));
	updates.push_back(sync_physics_body(game_world.puzzle2));
	updates.push_back(sync_physics_body(game_world.puzzle3));
	updates.push_back(sync_physics_body(game_world.puzzle4));
	updates.push_back(sync_physics_body(game_world.puzzle5));
	updates.push_back(sync_physics_body(game_world.puzzle6));

	updates.push_back(camera_track_object(main_camera, game_world.player.entity));
	updates.push_back(controls(game_world.player.entity, keyboard_events, grav_normal));

	updates.push_back(track_object_xy(game_world.background, game_world.player.entity));
	updates.push_back(respawn_player(game_world.player.entity, gui));

	updates.push_back(animate(time, game_world.player.entity, 8));
	updates.push_back(animate(time, game_world.lava, 15));
	updates.push_back(sync_player_animation(keyboard_events, game_world.player.entity));
	updates.push_back(player_health(game_world.player, game_world.enemy, gui));
	updates.push_back(player_damage_knockback(game_world.player, game_world.enemy));
	
	// GUI Interactions
	updates.push_back(
		from(keyboard_events, gui.settings_active, gui.settings_window->transform.position)
		.use(gui.make_toggle_settings([](auto a, auto b, auto c) { return c; }))
		.determine(gui.settings_window->transform.position));

	updates.push_back(
		from(keyboard_events, gui.settings_active, gui.music_slider->transform.position)
		.use(gui.make_toggle_settings(gui.slide_script))
		.determine(gui.music_slider->transform.position));

	updates.push_back(
		from(keyboard_events, gui.settings_active, gui.sfx_slider->transform.position)
		.use(gui.make_toggle_settings(gui.slide_script))
		.determine(gui.sfx_slider->transform.position));

	updates.push_back(
		from(keyboard_events, gui.settings_active)
		.use(switch_toggle)
		.determine(gui.settings_active));

	// Enemy "AI"
	updates.push_back(
		from(game_world.enemy->body, game_world.player.entity->body)
		.use(enemy_persue_player)
		.determine(game_world.enemy->body));
	updates.push_back(bounce(game_world.enemy, game_world.player.entity));
	updates.push_back(animate(time, game_world.enemy, 5));

	updates.push_back(end_game(game_world.player, current_level, game_world.puzzle3->id));
	updates.push_back(landing_sound<7>(game_world.player.entity, game_sounds.pearson_landing_sounds));
	updates.push_back(landing_sound<3>(game_world.enemy, game_sounds.monster_bounces));

	// Voice Clips
	updates.push_back(voice(delta_time, gui.slide_script.music_percent, gui.slide_script.sfx_percent));

	// Final Puzzle
	updates.push_back(raise_two_blocks(game_world.puzzle2, game_world.player));
	updates.push_back(raise_two_blocks(game_world.puzzle6, game_world.player));
	updates.push_back(raise_if_past(game_world.puzzle1, game_world.player));
	updates.push_back(move_right(game_world.puzzle3, game_world.player));
}