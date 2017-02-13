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
	: main_camera(glm::vec3(0, 0.0f, 2.0f)		// Position
				, glm::vec3(0.0, 0.5f, -10.0f)	// Focus
				, glm::vec3(0, 1.0f, 0)			// Up
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

void game_updates(vector<update_t<Level1&>>& updates, const Level1& prev) {

}