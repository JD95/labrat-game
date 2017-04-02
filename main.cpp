// C++ Headers
#include <string>
#include <iostream>
#include <tuple>
#include <functional>
#include <vector>
#include <glm.hpp>
#include <SDL.h>
#include <SDL_mixer.h>
#include <thread>
#include <chrono>


#include "../labrat/window/game.h"
#include "../labrat/utilities/function_view.h"
#include "../labrat/reactive/reactive.h"
#include "../labrat/utilities/SlotMap.h"
#include "../labrat/entity/entity.h"

#include "../labrat/reactive/source.h"

#include "Level1/Level1.h"

using std::vector;
using std::function;

#define NUM_WAVEFORMS 1
const char* _waveFileNames[] =
{
	"D:/Current_Project/labrat/OpenGL Wrapper/track.wav"
};

Mix_Chunk* _sample[2];

// Initializes the application data
int Init(void)
{
	memset(_sample, 0, sizeof(Mix_Chunk*) * 2);

	// Set up the audio stream
	int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
	if (result < 0)
	{
		fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
		exit(-1);
	}

	result = Mix_AllocateChannels(4);
	if (result < 0)
	{
		fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
		exit(-1);
	}

	// Load waveforms
	for (int i = 0; i < NUM_WAVEFORMS; i++)
	{
		_sample[i] = Mix_LoadWAV(_waveFileNames[i]);
		if (_sample[i] == NULL)
		{
			fprintf(stderr, Mix_GetError(), _waveFileNames[i]);
		}
	}

	return true;
}

int play_audio() {

	// Initialize the SDL library with the Video subsystem
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		atexit(SDL_Quit);

		SDL_Window* window = SDL_CreateWindow("DrumPads",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			256,
			256,
			SDL_WINDOW_RESIZABLE);

		// Application specific Initialize of data structures
		if (Init() == false)
			return -1;

		// Event descriptor
		SDL_Event Event;

		bool done = false;
		while (!done)
		{
			int gotEvent = SDL_PollEvent(&Event);

			while (!done && gotEvent)
			{
				switch (Event.type)
				{
				case SDL_KEYDOWN:
					switch (Event.key.keysym.sym)
					{
					case 'q':
						Mix_PlayChannel(-1, _sample[0], 0);
						break;
					case 'w':
						Mix_PlayChannel(-1, _sample[1], 0);
						break;
					default:
						break;
					}
					break;

				case SDL_QUIT:
					done = true;
					break;

				default:
					break;
				}
				if (!done) gotEvent = SDL_PollEvent(&Event);
			}
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(2s);

		}

		for (int i = 0; i < NUM_WAVEFORMS; i++)
		{
			Mix_FreeChunk(_sample[i]);
		}

		Mix_CloseAudio();
		SDL_Quit();
		return 0;
}

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

int test(int x, int y) { return x + y; }

void test_reactive_values() {
	Reactive<int> x(5);
	Reactive<int> y(5);
	Reactive<int> z(0);

	Reactive<std::string> foo("foo");
	Reactive<std::string> bar("bar");

	auto source = 
		from(x, y)
		.use([](int x, int y) { return x + y; })
		.determine(z);

	auto str_source =
		from(foo, bar)
		.use([](std::string f, std::string b) { return f + b; })
		.determine(foo);

	std::vector<std::unique_ptr<Updater>> ds;

	ds.push_back(std::move(source));
	ds.push_back(std::move(str_source));

	while (true) {
		x = 0;
		for(auto& d : ds) d->calculate();
		for (auto& d : ds) d->update();
		std::cout << z.value << std::endl;
		std::cout << foo.value << std::endl;
		system("pause");
	}
}

int main(int argc, char *argv[])
{
	play_audio();
	/*Game<Level1> super_alpha(std::string("labrat Engine - Super Alpha"), 1080,720);
	super_alpha.game();*/

	return 0;
}