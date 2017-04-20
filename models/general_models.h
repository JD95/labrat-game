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

inline auto repeating_texture_model(std::string filepath, GLfloat width, GLfloat height) {
	return Model{
		std::string("labrat-game/assets/" + filepath),
		std::vector<VertexData2D> {
		VertexData2D{ RGBA{ 0, height, 0, 255 },{ -1.0f, 1.00f }},
			VertexData2D{ RGBA{ width, 0, 0, 255 },{ 1.00f, -1.00f } },
			VertexData2D{ RGBA{ 0, 0, 0, 255 },{ -1.00f, -1.00f } },
			VertexData2D{ RGBA{ 0, height, 255, 255 },{ -1.00f, 1.00f } },
			VertexData2D{ RGBA{ width, 0, 255, 255 },{ 1.00f, -1.00f } },
			VertexData2D{ RGBA{ width, height, 255, 255 },{ 1.00f, 1.00f } },
	} };
}

inline auto basic_asset_model(std::string filepath) {
	return basic_model("labrat-game/assets/" + filepath);
}

inline auto player_model() {
	return basic_asset_model("player_animated.png");
}

inline auto ground_model(GLfloat width, GLfloat height) {
	return repeating_texture_model("platformTile.png", width, height);
}

inline auto friend_model() {
	return basic_asset_model("friend.png");
}

inline auto flower_model() {
	return basic_asset_model("flower.png");
}

inline auto spacebackground_model() {
	return basic_asset_model("spacebackground.png");
}

inline auto tree_model() {
	return basic_asset_model("tree.png");
}

inline auto goal_sign_model() {
	return basic_asset_model("goalsign.png");
}

inline auto levelcomplete_model() {
	return basic_asset_model("levelcomplete.png");
}


inline auto hp_segment_model() {
	return basic_asset_model("hpsegment1.png");
}

inline auto lava_model() {
	return basic_asset_model("lava.png");
}