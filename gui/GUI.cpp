#include "GUI.h"

GUI::GUI(SceneState & state)
{	
	// HP Bar
	int current_hp = 24;
	float hp_x_position = -0.95f, hp_y_position = 0.95f;

	for (int i = 0; i < current_hp; i++) {
		hp_bar.push_back(state.gui_spawn(hp_segment_model(), hp_x_position + (i * 0.025f), hp_y_position, 0.01f, 0.03f));
	}

}

GUI::~GUI()
{
}
