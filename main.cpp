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
#include "../labrat/utilities/SlotMap.h"
#include "../labrat/entity/entity.h"
#include "Level1.h"

using std::vector;
using std::function;

void print_id_list(SlotMap<Entity>& entities) {
	std::cout << "In use ID's\n";
	for (int i = 0; i < entities.first_free_index; i++)
	{
		std::cout << entities.id_list[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Free ID's\n";
	for (int i = entities.first_free_index; i < entities.first_free_index + 10; i++)
	{
		std::cout << entities.id_list[i] << " ";
	}
	std::cout << std::endl;
}

void test_slotmap() {
	SlotMap<Entity> entities;
	auto a = entities.create_object();
	auto b = entities.create_object();
	auto c = entities.create_object();

	print_id_list(entities);

	std::cout << "Destroying entity 1\n";

	entities.destroy_object(b);

	print_id_list(entities);

	std::cout << "Creating two more entities\n";

	auto d = entities.create_object();
	auto e = entities.create_object();

	print_id_list(entities);

	std::cout << "Trying to access destroyed entity\n";

	std::cout << (entities.get_object(b) == nullptr ? "Entity version destroyed successfully!\n" : "Entity version was not incremented!\n");

	system("pause");
}


int main(int argc, char *argv[])
{
	//test_slotmap();
	Game<Level1> super_alpha(std::string("labrat Engine - Super Alpha"), 1080,720);
	super_alpha.game();
	return 0;
}