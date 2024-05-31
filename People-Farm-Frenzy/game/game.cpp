#include "game.h"

#include "../gui/gui.h"
#include "../gui/window/window.h"

inline void GameLoop(Game* game) {
	// Part 1 Logic
	//
	std::vector<GameObject>& objects = game->GetGameObjects();


	static bool press = false;
	// This is a Animation Test
	{
		if (FloodGui::Context.IO.MouseInput[FloodMouseButton::FloodGuiButton_LeftMouse] && !press) {
			press = true;
			Human h;
			h.SetSize(140, 140);
			h.SetPosition(50, 50);
			h.GetSprite()->texture = GUI::gui->LoadTexture(GAME_BKG_FILENAME);
			h.set_time_left(0);
			h.SetType(GameObjectType_Human);
			objects.push_back(h);
		}
		else if (!FloodGui::Context.IO.MouseInput[FloodMouseButton::FloodGuiButton_LeftMouse]) {
			press = false;
		}
	}

	for (int j = 0; j < objects.size(); j++)
	{
		GameObject& obj = objects[j];
		GameObjectType type = obj.GetType();
		
		switch (type) {
			case GameObjectType_Human:
			{
				Human* human = reinterpret_cast<Human*>(&obj);
				
				if (human->get_time_left() <= 0) {

					human->set_exploded();

					/*
					 VISUAL EFFECTS
					*/
					{
						SFX explosion;
						explosion.nAttributes["type"] = SFXType_Fireball;
						explosion.SetType(GameObjectType_SFX);

						explosion.SetSize(140, 140);
						explosion.SetPosition(50, 50);


						explosion.GetSprite()->texture = GUI::gui->LoadTexture(SFXTextures[explosion.get_sfx_type()][0]);
						std::vector< LPDIRECT3DTEXTURE9>aniTexs;
						aniTexs.reserve(SFXTextures[explosion.get_sfx_type()].size());
						for (int i = 0; i < SFXTextures[explosion.get_sfx_type()].size(); i++) {
							LPCWSTR string = SFXTextures[explosion.get_sfx_type()][i];
							aniTexs.push_back(GUI::gui->LoadTexture(string));
						}
						std::vector<std::chrono::milliseconds>aniDelays;
						aniDelays.reserve(aniTexs.size());
						for (int i = 0; i < aniTexs.size(); i++)
							aniDelays.push_back(std::chrono::milliseconds(80));
						explosion.GetSprite()->Animations["default"] = Animation(aniTexs, aniDelays);
						objects.push_back(explosion);
						objects.back().GetSprite()->StartAnimation("default");
					}

					/*
					DROP ORGAN
					*/

					// Having an issue with this section
					// FIX THIS
					{
						Organ newOrgan = human->drop_new_organ();
						newOrgan.GetSprite()->texture = GUI::gui->LoadTexture(OrganTextures[(OrganTypes)newOrgan.nAttributes["type"]]);

						objects.push_back(newOrgan);
					}

					// Remove human from existance
					objects.erase(objects.begin() + j);
				}
				else {
					// Make them run to a certian place!
					//

				}
				break;
			}
			case GameObjectType_SFX: {
				SFX* sfx = reinterpret_cast<SFX*>(&obj);
				// Run though / update each animation frame if possible

				sfx->GetSprite()->UpdateAnimation();
				// If this animaiton ends then BYE BYE!!
				if (!sfx->GetSprite()->inAnimation)
					objects.erase(objects.begin() + j);
				break;
			}
			case GameObjectType_Organ:
			{
				Organ* organ = reinterpret_cast<Organ*>(&obj);

				// Check for hover by mouse
				// if organ is collected then
				// add to their data collecting 
				// dat shii

				break;
			}
			case GameObjectType_LivingSpace:
			{
				LivingSpace* livingspace = reinterpret_cast<LivingSpace*>(&obj);

				// While Button is not held refill current_capacity to full

				// While Button is held decrease curret_capacity
				// Spawm Humans

				break;
			}
			case GameObjectType_UFOCollector: {
				UFO* ufo = reinterpret_cast<UFO*>(&obj);

				// Loop through another ver. of
				// all the objects and filter for 
				// organs check which ones are in the radius
				// then yoink them.

				break;
			}
			
			default: {
				// Don't do shiii
			
				break;
			}
		}
	}
	
	// Part 2 Rendering
	/*
	RENDER SEQ.
		1. Draw Background / Ground

		2. Draw Living Spaces
		
		3. Draw Organs

		4. Draw Humans
		
		5. SFX

		5. Draw UFOs
	*/
	
	{
		// I did some sorting off camera
		//
		bool sort = true;
		while (sort) {
			sort = false;
			for (int i = 1; i < objects.size(); i++) {
				GameObject& obj1 = objects[i - 1];
				GameObject& obj2 = objects[i];

				const GameObjectType& type1 = obj1.GetType();
				const GameObjectType& type2 = obj2.GetType();

				if (type2 == GameObjectType_None && (type1 == GameObjectType_LivingSpace || type1 == GameObjectType_Organ || type1 == GameObjectType_Human || type1 == GameObjectType_UFOCollector || type1 == GameObjectType_SFX)) {
					sort = true;
					std::swap(obj1, obj2);
					break;
				}

				if (type2 == GameObjectType_LivingSpace && (type1 == GameObjectType_Organ || type1 == GameObjectType_Human || type1 == GameObjectType_UFOCollector || type1 == GameObjectType_SFX)) {
					sort = true;
					std::swap(obj1, obj2);
					break;
				}

				if (type2 == GameObjectType_Organ && (type1 == GameObjectType_Human || type1 == GameObjectType_UFOCollector || type1 == GameObjectType_SFX)) {
					sort = true;
					std::swap(obj1, obj2);
					break;
				}

				if (type2 == GameObjectType_SFX && (type1 == GameObjectType_Human || type1 == GameObjectType_UFOCollector)) {
					sort = true;
					std::swap(obj1, obj2);
					break;
				}

				if (type2 == GameObjectType_Human && (type1 == GameObjectType_UFOCollector)) {
					sort = true;
					std::swap(obj1, obj2);
					break;
				}
			}
		}
	}
	FloodDrawList* drawList = FloodGui::Context.GetBackgroundDrawList();

	drawList->AddRectFilled(FloodVector2(), FloodGui::Context.Display.DisplaySize, FloodColor(1.f, 1.f, 1.f), GUI::gui->LoadTexture(GAME_BKG_FILENAME));
	for (GameObject& obj : objects) {
		Sprite* sprite = obj.GetSprite();
		if (obj.GetType() == GameObjectType_None || !sprite->texture)
			continue;
		
		drawList->AddRectFilled(FloodVector2(sprite->left, sprite->top), FloodVector2(sprite->right, sprite->bottom), FloodColor(1.f, 1.f, 1.f), sprite->texture);
	}
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
		
		for (int i = 0; i < 4; i++) {
			gameData.LivingSpaceUpgrades[i].level = 0;
			gameData.LivingSpaceUpgrades[i].levelMax = LivingSpaceNames.size() - 1;
			gameData.LivingSpaceUpgrades[i].Value.nAttributes["type"] = LivingSpaceType_None;
			gameData.LivingSpaceUpgrades[i].Value.nAttributes["current_capacity"] = LivingSpaceCapacity[(LivingSpaceTypes)static_cast<int>(gameData.LivingSpaceUpgrades[i].Value.nAttributes["type"])];
		}
		gameData.ButtonMultiplier.level = 0;
		gameData.ButtonMultiplier.levelMax = 100;
	}

	std::srand(time(NULL));
}

void Game::InitalizeGameGraphics() {
	// Initalize Game Data should be called before this.
	//
	GUI::window = new Window(800, 700);
	GUI::gui = new Gui(GUI::window);

	GUI::window->Initalize(GUI::gui);

	GUI::gui->AddRenderHandle((render_handle_fn)GameLoop, this);

	GUI::gui->RunFlood();
}

std::vector<GameObject>& Game::GetGameObjects() { return GameObjects; }