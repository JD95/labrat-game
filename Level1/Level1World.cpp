#include "Level1World.h"



Level1World::Level1World(SceneState& state)
{
	//// Props
	//	background = state.spawn(spacebackground_model(),
	//		Transform(glm::vec3(0.0f, 0.0f, background_layer), glm::vec3(10.0f)));

	//for (int i = 0; i < 3; i++)
	//	trees.push_back(state.spawn_massless(tree_model(), scenary_layer, -2.25f + i*1.5f, 0.0f, 1.0f, 1.0f));

	//flower = state.spawn_massless(flower_model(), scenary_layer + 0.1f, -2.5f, 0.0f, 1.0f, 1.0f);
	//goal_sign = state.spawn_massless(goal_sign_model(), scenary_layer, 2.0, -0.5, 3.0f, 3.0f);


	// Platforms 
	platform1 = state.spawn_body(ground_model(), playable_layer, 0.0f, -1.0f, 20.0f, 1.0f, 0.0f);
	//rising_platform = state.spawn_body(ground_model(), playable_layer, 4.0f, -1.0f, 2.0f, 1.0f, 0.0f);
	//platform2 = state.spawn_body(ground_model(), playable_layer, 8.0f, -1.0f, 5.0f, 1.0f, 0.0f);


	// Units
	player = state.spawn_body(player_model(), playable_layer, 0.0f, 3.0f, 1.0f, 1.0f, 2.0f);

	friend_bot1 = state.spawn_body(friend_model(), playable_layer, 3.5f, 2.0f, 0.5f, 0.5f, 1.0f);
	friend_bot2 = state.spawn_body(friend_model(), playable_layer, -3.0f, 3.0f, 0.5f, 0.5f, 1.0f);

	//level_complete_sign = state.spawn_massless(levelcomplete_model(), -10.0f, 0.0f, 0.0f, 5.0f, 5.0f);
}


Level1World::~Level1World()
{
}
