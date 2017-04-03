#include "GUI.h"

GUI::GUI(SceneState & state)
{
	austinSquare = state.gui_spawn(flower_model(), -0.10f, 0.75f, 0.25f, 0.25f);

}

GUI::~GUI()
{
}
