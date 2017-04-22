#include "Player.h"

Player::Player()
	: entity(NULL)
	, health(0)
{
}

Player::Player(Entity* e, int hp)
	: entity()
	, health(hp)
{
}

Player::~Player()
{
}
