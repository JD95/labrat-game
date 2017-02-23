#include "Level1.h"

#include <vector>

#include "../labrat/primitive_shapes/polygon.h"
#include "../labrat/entity/transform.h"
#include "../labrat/scene/camera.h"
#include "../labrat/utilities/units.h"
#include "../labrat/entity/entity.h"
#include "../labrat/graphics/model.h"
#include "../labrat/opengl/vertexdata.h"


Level1::Level1()
	: main_camera(Camera( glm::vec3(0, 0.0f, 2.0f)		// Position
						, glm::vec3(0.0, 0.5f, -10.0f)	// Focus
						, glm::vec3(0, 1.0f, 0))		// Up
				)
{
	Model logo { 
		std::string("labrat-game/logo.png"),
		std::vector<VertexData2D> {
			{ { 0, 1, 0, 255 },{ -0.90f, 0.90f }},
			{ { 1, 0, 0, 255 },{ 0.90f, -0.90f } },
			{ { 0, 0, 0, 255 },{ -0.90f, -0.90f } },
			{ { 0, 1, 255, 255 },{ -0.90f, 0.90f } },
			{ { 1, 0, 255, 255 },{ 0.90f, -0.90f } },
			{ { 1, 1, 255, 255 },{ 0.90f, 0.90f } },
	}};

	Transform t(glm::vec3(0, 0.0f, 0), glm::vec3(1.0f, 1.0f, 1.0f));

	picture1 = spawn(logo, t);

	t.position[1] += 2;

	picture2 = spawn(logo, t);
}


Level1::~Level1()
{
}

update_t<Level1&> move_camera_bindings(Camera& c, SDL_Event event) {
	return [&c, event](auto& l){
		// Negative because we are moving the world not the camera
		const float camera_speed = 0.05f;
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			c.position[1] += camera_speed;
			c.focus[1] += camera_speed;
			break;
		case SDLK_s:
			c.position[1] -= camera_speed;
			c.focus[1] -= camera_speed;
			break;
		case  SDLK_a:
			c.position[0] -= camera_speed;
			c.focus[0] -= camera_speed;
			break;
		case SDLK_d:
			c.position[0] += camera_speed;
			c.focus[0] += camera_speed;
			break;
		case SDLK_UP:
			c.rotate_camera(camera_speed, 0, 0);
			break;
		case SDLK_DOWN:
			c.rotate_camera(-1 * camera_speed, 0, 0);
			break;
		case  SDLK_LEFT:
			c.rotate_camera(0, camera_speed, 0);
			break;
		case SDLK_RIGHT:
			c.rotate_camera(0, -1 * camera_speed, 0);
			break;
		default: break;
		}
	};	
}

void Level1::construct_updates(vector<update_t<Level1&>>& updates, const vector<SDL_Event>& keyboard_events, const Level1& prev) {
	if (keyboard_events.size() > 0)
		updates.push_back(move_camera_bindings(main_camera, keyboard_events[0]));
}