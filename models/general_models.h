#pragma once

#include <string>

inline auto basic_model(std::string filepath) {
	return Model{
		std::string(filepath),
		std::vector<VertexData2D> {
			{ { 0, 1, 0, 255 },{ -0.90f, 0.90f }},
			{ { 1, 0, 0, 255 },{ 0.90f, -0.90f } },
			{ { 0, 0, 0, 255 },{ -0.90f, -0.90f } },
			{ { 0, 1, 255, 255 },{ -0.90f, 0.90f } },
			{ { 1, 0, 255, 255 },{ 0.90f, -0.90f } },
			{ { 1, 1, 255, 255 },{ 0.90f, 0.90f } },
	} };
}

inline auto player_model() {
	return basic_model("labrat-game/player.png");
}

inline auto ground_model() {
	return basic_model("labrat-game/ground.png");
}

inline auto friend_model() {
	return basic_model("labrat-game/friend.png");
}