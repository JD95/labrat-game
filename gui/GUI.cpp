#include "GUI.h"

GUI::GUI(SceneState & state)
	: level(state)
{	

	// HP Bar
	current_hp = 24;
	hp_x_position = -0.95f;
	hp_y_position = 0.95f;

	flower = state.gui_spawn(goal_sign_model(), 10.0f, 10.0f, 0.2f, 0.2f);

	for (int i = 0; i < current_hp; i++) {
		hp_bar.push_back(state.gui_spawn(hp_segment_model(), hp_x_position + (i * 0.025f), hp_y_position, 0.01f, 0.03f));
	}

	

}

GUI::~GUI()
{
}

void GUI::lose_hp()
{
	current_hp--;
	if (current_hp >= 0) {
		level.gui_entities.destroy_object(hp_bar[current_hp]->id);
	}
}
