#pragma once

#include "../../labrat/entity/entity.h"
#include "../../labrat/reactive/reactive.h"

struct Player
{
	Reactive<int> health;
	Entity* entity;

	Player();
	Player(Entity* entity, int hp);
	~Player();
};

