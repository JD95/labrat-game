#include "Level1World.h"



Level1World::Level1World(SceneState& state)
{
	//for (int i = 0; i < 3; i++)
	background = state.spawn_massless(spacebackground_model(), background_layer, 0.0f,0.0f,20.0f,20.0f);

	// Platforms 
	auto platform = [&state](float x, float y, float width, float height) {
		return state.spawn_body(ground_model(width, height), playable_layer,x,y,width,height, 0.0f);
	};

	// Static platforms
	platforms.push_back(platform(0.0f, -1.0f, 10.0f, 1.0f));
	platforms.push_back(platform(0.0f, 0.0f, 1.0f, 5.0f));
	platforms.push_back(platform(10.0f, 0.55f, 5.0f, 0.25f));
	platforms.push_back(platform(14.0f, 1.0f, 1.0f, 3.0f));
	platforms.push_back(platform(7.00f, 1.25f, 2.0f, 0.25f));
	platforms.push_back(platform(4.25f, 1.55f, 2.0f, 0.25f));
	platforms.push_back(platform(1.25f, 2.25f, 2.0f, 0.25f));
	platforms.push_back(platform(4.25f, 3.00f, 2.0f, 0.25f));
	platforms.push_back(platform(7.00f, 3.25f, 2.0f, 0.25f));
	platforms.push_back(platform(10.0f, 4.00f, 10.0f, 0.25f));
	platforms.push_back(platform(32.0f, 4.00f, 10.0f, 0.25f));

	goal_sign = state.spawn_massless(goal_sign_model(), scenary_layer, 32.0f, 4.25f, 2.0f, 2.0f);

	for (int i = 0; i < 3; i++)
	{
		rising_platforms.push_back(state.spawn_body(ground_model(21.0f + i*4.1f, 4.0f), playable_layer, 21.0f + i*4.1f, 4.0f, 2.0f, 1.0f, 0.0f));
	}

	// Units
	player.entity = state.spawn_body(player_model(), playable_layer, 1.0f, 1.0f, 0.5f, 0.5f, 2.0f);
	player.health = 24;

	enemy = state.spawn_body(enemy_model(), playable_layer, 5.0f, 1.0f, 0.5f, 0.5f, 2.0f);

	lava = state.spawn_massless(lava_model(), 0.1f, 15.0f, -1.0f, 20.0f, 5.5f);
}


Level1World::~Level1World()
{
}
