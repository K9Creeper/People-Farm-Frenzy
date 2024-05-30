#include "game.h"

#include "../gui/gui.h"
#include "../gui/window/window.h"

inline void GameLoop(Game* game) {

}

Game::Game() {

}

Game::~Game() {

}

void Game::InitalizeGameData() {
	// Retrive Game Saves???
	//

	// If a save is unretrivable
	// initalize a new save

	bool newSave = true;

	// Todo:
	//		1. Retrieve Game Saves

	if(newSave)
	{
		gameData.Glorbux = 0;
		
		for (int i = 0; i < LivingSpaceNames.size(); i++) {
			gameData.LivingSpaceUpgrades[i].level = 0;
			gameData.LivingSpaceUpgrades[i].levelMax = LivingSpaceNames.size() - 1;
			gameData.LivingSpaceUpgrades[i].Value.nAttributes["type"] = LivingSpaceType_None;
		}
		gameData.ButtonMultiplier.level = 0;
		gameData.ButtonMultiplier.levelMax = 100;
	}
}

void Game::InitalizeGameGraphics() {
	// Initalize Game Data should be called before this.
	//
	GUI::window = new Window(700, 600);
	GUI::gui = new Gui(GUI::window);

	GUI::window->Initalize(GUI::gui);

	GUI::gui->AddRenderHandle((render_handle_fn)GameLoop, this);

	GUI::gui->RunFlood();
}
