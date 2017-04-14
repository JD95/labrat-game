#pragma once

#include <string>

inline auto basic_model(std::string filepath) {
	return Model{
		std::string(filepath),
		std::vector<VertexData2D> {
			{ { 0, 1, 0, 255 },{ -1.0f, 1.00f }},
			{ { 1, 0, 0, 255 },{ 1.00f, -1.00f } },
			{ { 0, 0, 0, 255 },{ -1.00f, -1.00f } },
			{ { 0, 1, 255, 255 },{ -1.00f, 1.00f } },
			{ { 1, 0, 255, 255 },{ 1.00f, -1.00f } },
			{ { 1, 1, 255, 255 },{ 1.00f, 1.00f } },
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

inline auto flower_model() {
	return basic_model("labrat-game/flower.png");
}

inline auto spacebackground_model() {
	return basic_model("labrat-game/spacebackground.png");
}

inline auto tree_model() {
	return basic_model("labrat-game/tree.png");
}

inline auto goal_sign_model() {
	return basic_model("labrat-game/goalsign.png");
}

inline auto levelcomplete_model() {
	return basic_model("labrat-game/levelcomplete.png");
}


inline auto hp_segment_model() {
	return basic_model("labrat-game/hpsegment1.png");
}

inline auto lava_model() {
	return basic_model("labrat-game/lava.png");
}