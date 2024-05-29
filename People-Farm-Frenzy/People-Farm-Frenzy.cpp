#include <iostream>

#include "gui/gui.h"
#include "gui/window/window.h"

void RenderTest() {
    static auto texture = GUI::gui->LoadTexture(L"SpriteTest.jpg");
    FloodGui::Context.GetBackgroundDrawList()->AddRectFilled(FloodVector2(0, 0), FloodVector2(300, 300), FloodColor(1, 1, 1), texture);
}

int main()
{
    //This is going to be a test of the GUI
    //

    GUI::window = new Window(700, 600);
    GUI::gui = new Gui(GUI::window);

    GUI::window->Initalize(GUI::gui);
    GUI::gui->AddRenderHandle((render_handle_fn)RenderTest);
    GUI::gui->RunFlood();

    delete GUI::gui;
    delete GUI::window;
}