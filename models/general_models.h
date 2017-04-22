#pragma once

#include <string>
#include <vector>
#include "../../labrat/texture/SpriteSheet.h"

const std::vector<VertexData2D> default_vertex_data = 
	std::vector<VertexData2D>{
		{ { 0, 1, 0, 255 },{ -1.0f, 1.00f } },
		{ { 1, 0, 0, 255 },{ 1.00f, -1.00f } },
		{ { 0, 0, 0, 255 },{ -1.00f, -1.00f } },
		{ { 0, 1, 255, 255 },{ -1.00f, 1.00f } },
		{ { 1, 0, 255, 255 },{ 1.00f, -1.00f } },
		{ { 1, 1, 255, 255 },{ 1.00f, 1.00f } },
	};

inline std::string asset_path(std::string path) { return "labrat-game/assets/" + path; }

inline auto basic_model(std::string filepath) {
	return Model{ std::string(filepath), default_vertex_data };
}


inline auto repeating_texture_model(std::string filepath, GLfloat width, GLfloat height) {
	return Model{
		asset_path(filepath),
		std::vector<VertexData2D> {
		VertexData2D{ RGBA{ 0, height, 0, 255 },{ -1.0f, 1.00f }},
			VertexData2D{ RGBA{ width, 0, 0, 255 },{ 1.00f, -1.00f } },
			VertexData2D{ RGBA{ 0, 0, 0, 255 },{ -1.00f, -1.00f } },
			VertexData2D{ RGBA{ 0, height, 255, 255 },{ -1.00f, 1.00f } },
			VertexData2D{ RGBA{ width, 0, 255, 255 },{ 1.00f, -1.00f } },
			VertexData2D{ RGBA{ width, height, 255, 255 },{ 1.00f, 1.00f } },
	} };
}

inline auto animated_model(std::string filepath, unsigned int rows, unsigned int cols, std::vector<Animation> as) {
	return AnimatedModel(asset_path(filepath), rows, cols, as, default_vertex_data);
}

inline auto basic_asset_model(std::string filepath) {
	return basic_model(asset_path(filepath));
}

inline auto player_model() {
	return animated_model("bi_directional_stick.png", 3, 8, {
		Animation{ { 0,0 },{ 0,0 } },
		Animation { { 1,0 }, { 1,7 } },
		Animation { { 2,0 }, { 2,7 } }
	});
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