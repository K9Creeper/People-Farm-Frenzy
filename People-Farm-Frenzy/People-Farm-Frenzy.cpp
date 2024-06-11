#include <iostream>

#include "gui/gui.h"
#include "game/soundsystem/soundsystem.h"
#include "gui/window/window.h"
#include "game/game.h"


int CALLBACK WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       lpCmdLine,
    int         nCmdShow
) {
    //This is going to be a test of the GUI
    //
    Game game;
    game.InitalizeGameData();    
    game.InitalizeGameSound();
    game.InitalizeGameGraphics();

    delete soundSystem;
    delete GUI::gui;
    delete GUI::window;
}