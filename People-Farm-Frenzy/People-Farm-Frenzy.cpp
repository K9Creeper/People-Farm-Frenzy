#include <iostream>

#include "gui/gui.h"
#include "gui/window/window.h"
#include "game/game.h"


int main()
{
    //This is going to be a test of the GUI
    //
    Game game;
    game.InitalizeGameData();
    game.InitalizeGameGraphics();

    delete GUI::gui;
    delete GUI::window;
}