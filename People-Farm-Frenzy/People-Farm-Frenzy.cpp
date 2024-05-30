#include <iostream>

#include "gui/gui.h"
#include "gui/window/window.h"

void RenderTest(void* unused) {
    static auto texture = GUI::gui->LoadTexture(L"SpriteTest.jpg");
    FloodGui::Context.GetBackgroundDrawList()->AddRectFilled(FloodVector2(0, 0), FloodVector2(300, 300), FloodColor(255, 255, 255, 255), texture);
}

int main()
{
    //This is going to be a test of the GUI
    //

   

    delete GUI::gui;
    delete GUI::window;
}