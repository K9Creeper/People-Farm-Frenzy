#include "game.h"

#include "../gui/gui.h"
#include "../gui/window/window.h"

void SpawnUFO(std::vector<GameObject>& objects, const int& x, const int& y, const int& width, const int& height)
{
	UFO h;
	h.SetSize(width, height);
	h.SetPosition(x, y);
	h.GetSprite()->texture = GUI::gui->LoadTexture(UFOAnimationLoop[0]);
	std::vector< LPDIRECT3DTEXTURE9>aniTexs;
	aniTexs.reserve(UFOAnimationLoop.size());
	for (int i = 0; i < UFOAnimationLoop.size(); i++) {
		LPCWSTR string = UFOAnimationLoop[i];
		aniTexs.push_back(GUI::gui->LoadTexture(string));
	}
	std::vector<std::chrono::milliseconds>aniDelays;
	aniDelays.reserve(aniTexs.size());
	for (int i = 0; i < aniTexs.size(); i++)
		aniDelays.push_back(std::chrono::milliseconds(80));
	h.GetSprite()->AddAnimation("default", Animation(aniTexs, aniDelays));
	h.SetType(GameObjectType_UFOCollector);
	objects.push_back(h);
}

void SpawnHuman(std::vector<GameObject>& objects, const int& x, const int& y, const int& width, const int& height) {
	Human h;
	h.SetSize(width, height);
	h.SetPosition(x, y);
	h.GetSprite()->texture = GUI::gui->LoadTexture(L"resources/sprites/SpriteTest.jpg");
	h.set_exploded(false);
	h.set_time_left(2500);
	h.SetType(GameObjectType_Human);
	objects.push_back(h);
}

void SpawnVFXBloodCloud(std::vector<GameObject>& objects, const int& x, const int& y, const int& width, const int& height) {
	VFX explosion;
	explosion.nAttributes["type"] = VFXType_BloodCloud;
	explosion.SetType(GameObjectType_VFX);

	explosion.SetSize(width, height);
	explosion.SetPosition(x, y);


	explosion.GetSprite()->texture = GUI::gui->LoadTexture(VFXTextures[explosion.get_vfx_type()][0]);
	std::vector< LPDIRECT3DTEXTURE9>aniTexs;
	aniTexs.reserve(VFXTextures[explosion.get_vfx_type()].size());
	for (int i = 0; i < VFXTextures[explosion.get_vfx_type()].size(); i++) {
		LPCWSTR string = VFXTextures[explosion.get_vfx_type()][i];
		aniTexs.push_back(GUI::gui->LoadTexture(string));
	}
	std::vector<std::chrono::milliseconds>aniDelays;
	aniDelays.reserve(aniTexs.size());
	for (int i = 0; i < aniTexs.size(); i++)
		aniDelays.push_back(std::chrono::milliseconds(80));
	explosion.GetSprite()->AddAnimation("default",Animation(aniTexs, aniDelays));
	objects.push_back(explosion);
	objects.back().GetSprite()->StartAnimation("default");
}

void SpawnVFXBloodClouds(std::vector<GameObject>& objects, const int& x, const int& y, const int& width, const int& height, const int& offsetPer = 2) {
	SpawnVFXBloodCloud(objects, x + offsetPer, y + offsetPer, width, height);
	SpawnVFXBloodCloud(objects, x - offsetPer, y - offsetPer, width, height);
	SpawnVFXBloodCloud(objects, x - offsetPer, y + offsetPer, width, height);
	SpawnVFXBloodCloud(objects, x + offsetPer, y - offsetPer, width, height);

	SpawnVFXBloodCloud(objects, x, y - offsetPer, width, height);
	SpawnVFXBloodCloud(objects, x, y + offsetPer, width, height);
	SpawnVFXBloodCloud(objects, x - offsetPer, y , width, height);
	SpawnVFXBloodCloud(objects, x + offsetPer, y , width, height);
}

Organ drop_new_organ(const int& x, const int& y, const int& width, const int& height) {
	double random = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

	Organ organ;
	organ.SetType(GameObjectType_Organ);
	double Chance = 1.f;

	if (random <= Chance) {
		organ.nAttributes["type"] = OrganType_Brain;
	}
	Chance -= OrganChances[OrganType_Brain];
	if (random <= Chance) {
		organ.nAttributes["type"] = OrganType_Heart;

	}
	Chance -= OrganChances[OrganType_Heart];
	if (random <= Chance) {
		organ.nAttributes["type"] = OrganType_Lung;

	}
	Chance -= OrganChances[OrganType_Lung];
	if (random <= Chance) {
		organ.nAttributes["type"] = OrganType_Kidney;

	}
	Chance -= OrganChances[OrganType_Kidney];
	if (random <= Chance) {
		organ.nAttributes["type"] = OrganType_Eyeball;

	}
	Chance -= OrganChances[OrganType_Eyeball];
	if (random <= Chance) {
		organ.nAttributes["type"] = OrganType_Intestine;

	}
	Chance -= OrganChances[OrganType_Intestine];
	if (random <= Chance) {
		organ.nAttributes["type"] = OrganType_Stomach;
	}
	Chance -= OrganChances[OrganType_Stomach];
	if (random <= Chance) {
		organ.nAttributes["type"] = OrganType_Skin;
	}
	Chance -= OrganChances[OrganType_Skin];
	if (random <= Chance) {
		organ.nAttributes["type"] = OrganType_Skull;
	}
	Chance -= OrganChances[OrganType_Skull];

	organ.SetSize(width, height);
	organ.SetPosition(x, y);

	organ.nAttributes["value"] = OrganValues[(OrganTypes)organ.nAttributes["type"]];
	organ.sAttributes["name"] = OrganNames[(OrganTypes)organ.nAttributes["type"]];

	return organ;
}

inline void GameLoop(Game* game) {
	// Part 1 Logic
	//
	std::vector<GameObject>& objects = game->GetGameObjects();
	GameData* gameData = game->GetGameData();

	static bool press = false;
	// This is a Animation Test
	{
		if (FloodGui::Context.IO.MouseInput[FloodMouseButton::FloodGuiButton_LeftMouse] && !press) {
			press = true;
			
			SpawnHuman(objects, FloodGui::Context.IO.mouse_pos.x, FloodGui::Context.IO.mouse_pos.y, 80 , 80);
		}
		else if (!FloodGui::Context.IO.MouseInput[FloodMouseButton::FloodGuiButton_LeftMouse]) {
			press = false;
		}
	}
	static std::chrono::milliseconds lastLoop = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	for (int j = 0; j < objects.size(); j++)
	{

		GameObject& obj = objects[j];
		GameObjectType type = obj.GetType();
		
		FloodVector2 pos = FloodVector2(obj.GetSprite()->x, obj.GetSprite()->y);

		switch (type) {
			case GameObjectType_Human:
			{
				Human* human = reinterpret_cast<Human*>(&obj);

				if (human->get_exploded()) {
					// Remove human from existance
					objects.erase(objects.begin() + j);
					break;
				}

				if (human->get_time_left() <= 0) {
					human->set_exploded();

					/*
					 VISUAL EFFECTS
					*/

					#ifdef ENHANCE_VFXBLOOD_CLOUDS
						SpawnVFXBloodClouds(objects, pos.x, pos.y, 95, 95);
					#else
						SpawnVFXBloodCloud(objects, pos.x, pos.y, 95, 95);
					#endif // ENHANCE_VFXBLOOD_CLOUDS
					
					Organ newOrgan = drop_new_organ(pos.x, pos.y, 40, 40);
					newOrgan.GetSprite()->texture = GUI::gui->LoadTexture(OrganTextures[(OrganTypes)newOrgan.nAttributes["type"]]);
					objects.push_back(newOrgan);
				}
				else {
					// Make them run to a certian place!
					//
					human->SetPosition(human->GetSprite()->x + 1, human->GetSprite()->y + 1);

					human->set_time_left(human->get_time_left()-((now -lastLoop).count()));
				}
				break;
			}
			case GameObjectType_VFX: {
				VFX* vfx = reinterpret_cast<VFX*>(&obj);
				// Run though / update each animation frame if possible

				vfx->GetSprite()->UpdateAnimation();
				// If this animaiton ends then BYE BYE!!
				if (!vfx->GetSprite()->inAnimation) {
					if (vfx->get_vfx_type() == VFXType_BloodCloud)
					{
						
					}
					objects.erase(objects.begin() + j);
				}
				break;
			}
			case GameObjectType_Organ:
			{
				Organ* organ = reinterpret_cast<Organ*>(&obj);

				// Check for hover by mouse
				// if organ is collected then
				// add to their data collecting 
				// dat shii

				if (FloodGui::Context.IO.mouse_pos.x >= organ->GetSprite()->left && FloodGui::Context.IO.mouse_pos.x <= organ->GetSprite()->right && FloodGui::Context.IO.mouse_pos.y >= organ->GetSprite()->top && FloodGui::Context.IO.mouse_pos.y <= organ->GetSprite()->bottom)
				{
					// Collect that shiii
					const float& price = organ->get_value();
					

					// Get rid of on screen
					objects.erase(objects.begin() + j);
				}
				break;
			}
			case GameObjectType_LivingSpace:
			{
				LivingSpace* livingspace = reinterpret_cast<LivingSpace*>(&obj);

				if (livingspace->get_space_type() == LivingSpaceType_None)
					break;

				bool buttonPressed = false;
				// While Button is held decrease curret_capacity - Spawm Humans
				// While Button is not held refill current_capacity to full (at a rate)

				if (buttonPressed) {
					//if(livingspace->get_current_capacity() )
				}
				else {
					//livingspace->set_current_capacity();

				}

				

				break;
			}
			case GameObjectType_UFOCollector: {
				UFO* ufo = reinterpret_cast<UFO*>(&obj);

				// Loop through another ver. of
				// all the objects and filter for 
				// organs check which ones are in the radius
				// then yoink them.

				ufo->GetSprite()->UpdateAnimation();

				if (!ufo->GetSprite()->inAnimation)
					ufo->GetSprite()->StartAnimation("default");				
				

				// FLY AROUND


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

		2. Draw Background / Enviorment VFX

		3. Draw Living Spaces
		
		4. Draw Organs

		5. Draw Humans
		
		6. VFX

		7. Draw UFOs
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

				if (type2 == GameObjectType_None && (type1 == GameObjectType_VFXEnviorment || type1 == GameObjectType_LivingSpace || type1 == GameObjectType_Organ || type1 == GameObjectType_Human || type1 == GameObjectType_UFOCollector || type1 == GameObjectType_VFX)) {
					sort = true;
					std::swap(obj1, obj2);
					break;
				}

				if (type2 == GameObjectType_VFXEnviorment && (type1 == GameObjectType_LivingSpace || type1 == GameObjectType_Organ || type1 == GameObjectType_Human || type1 == GameObjectType_UFOCollector || type1 == GameObjectType_VFX)) {
					sort = true;
					std::swap(obj1, obj2);
					break;
				}

				if (type2 == GameObjectType_LivingSpace && (type1 == GameObjectType_Organ || type1 == GameObjectType_Human || type1 == GameObjectType_UFOCollector || type1 == GameObjectType_VFX)) {
					sort = true;
					std::swap(obj1, obj2);
					break;
				}

				if (type2 == GameObjectType_Organ && (type1 == GameObjectType_Human || type1 == GameObjectType_UFOCollector || type1 == GameObjectType_VFX)) {
					sort = true;
					std::swap(obj1, obj2);
					break;
				}

				if (type2 == GameObjectType_VFX && (type1 == GameObjectType_Human || type1 == GameObjectType_UFOCollector)) {
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
	static int frame = 0;
	static std::chrono::milliseconds lastFrame = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::chrono::milliseconds now2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	if (now2 - std::chrono::milliseconds(280) >= lastFrame) {
		frame++;
		lastFrame = now2;
	}
	if (frame >= BackgroundFrames.size())
		frame = 0;
	drawList->AddRectFilled(FloodVector2(), FloodGui::Context.Display.DisplaySize, FloodColor(1.f, 1.f, 1.f), GUI::gui->LoadTexture(BackgroundFrames[frame]));
	
	for (GameObject& obj : objects) {
		Sprite* sprite = obj.GetSprite();
		if (obj.GetType() == GameObjectType_None || !sprite->texture)
			continue;
		if (obj.GetType() == GameObjectType_Organ)
		{

		}
		drawList->AddRectFilled(FloodVector2(sprite->left, sprite->top), FloodVector2(sprite->right, sprite->bottom), FloodColor(1.f, 1.f, 1.f), sprite->texture);
	}
	lastLoop = now;
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
		
		for (int i = 0; i < 3; i++) {
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
	GUI::window = new Window(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	GUI::gui = new Gui(GUI::window);

	GUI::window->Initalize(GUI::gui);

	GUI::gui->AddRenderHandle((render_handle_fn)GameLoop, this);

	GUI::gui->RunFlood();
}

std::vector<GameObject>& Game::GetGameObjects() { return GameObjects; }

GameData* Game::GetGameData() { return &gameData; }

