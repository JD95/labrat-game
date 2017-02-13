// C++ Headers
#include <string>
#include <iostream>
#include <tuple>
#include <functional>
#include <vector>
#include <glm.hpp>
#include <SDL.h>

#include "../labrat/window/game.h"
#include "../labrat/utilities/function_view.h"
#include "../labrat/reactive/reactive.h"
#include "Level1.h"

using std::vector;
using std::function;


int main(int argc, char *argv[])
{
	Game<Level1> super_alpha(std::string("labrat Engine - Super Alpha"), 1080,720);
	super_alpha.game(game_updates);
	return 0;
}