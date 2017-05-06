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

inline auto ground_model(GLfloat width, GLfloat height) {
	return repeating_texture_model("platformTile.png", width, height);
}

inline auto player_model() {
	return animated_model("SpaceManFullSprite.png", 7, 7, {
		Animation { { 0,0 }, { 0,1 } },
		Animation{ { 1,0 },{ 1,5 } },
		Animation{ { 2,0 },{ 2,5 } },
		Animation{ { 3,0 },{ 3,5 } },
		Animation{ { 4,0 },{ 4,6 } },
		Animation{ { 5,0 },{ 5,6 } },
		Animation{ { 6,0 },{ 6,6 } },
	});
}

inline auto enemy_model() {
	return animated_model("EnemySprite.png", 2, 11, {
		Animation{ { 0,0 },{ 0,10 } },
	});
}

inline auto lava_model() {
	return animated_model("LavaSprite.png", 1, 22, {
		Animation{ { 0,0 },{ 0,21 } }
	});
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

inline auto settings_shortcut_model() {
	return basic_asset_model("settingsshortcut.png");
}

inline auto slider_model() {
	return basic_asset_model("settingsslider.png");
}

inline auto settings_model() {
	return basic_asset_model("settingsbackground.png");
}