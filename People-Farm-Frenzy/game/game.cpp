#include "game.h"

#include "../gui/gui.h"
#include "../gui/window/window.h"

#include "graphics/interact/interact.h"
#include "soundsystem/soundsystem.h"

#include <iostream>

void SpawnUFO(std::vector<std::shared_ptr<GameObject>>& objects, const int& x, const int& y, const int& width, const int& height)
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
	objects.push_back(std::make_shared<GameObject>(h));
}

void SpawnHuman(std::vector<std::shared_ptr<GameObject>>& objects, const int& x, const int& y, const int& width, const int& height) {

	Human h;
	h.SetSize(width, height);
	h.SetPosition(x, y);
	{
		double random = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		double Chance = 1.f;

		h.set_human_type(HumanType_Boy1);
		if (random <= Chance) {
			h.set_human_type(HumanType_Bert);
		}
		Chance -= HumanChances[HumanType_Bert];
		if (random <= Chance) {
			h.set_human_type(HumanType_Boy1);
		}
		Chance -= HumanChances[HumanType_Boy1];
		if (random <= Chance) {
			h.set_human_type(HumanType_Boy2);
		}
		Chance -= HumanChances[HumanType_Boy2];
		if (random <= Chance) {
			h.set_human_type(HumanType_Boy3);
		}
		Chance -= HumanChances[HumanType_Boy3];
		if (random <= Chance) {
			h.set_human_type(HumanType_Girl1);
		}
		Chance -= HumanChances[HumanType_Girl1];
		if (random <= Chance) {
			h.set_human_type(HumanType_Girl2);
		}
		Chance -= HumanChances[HumanType_Girl2];

		h.GetSprite()->texture = GUI::gui->LoadTexture(HumanTextures[(HumanTypes)h.nAttributes["type"]]);
	}
	
	// Load animations
	for (const auto& [string, frames] : HumanAnimations[(HumanTypes)h.nAttributes["type"]]) {
		std::vector<std::chrono::milliseconds>aniDelays;
		for (int i = 0; i < frames.size(); i++)
			aniDelays.push_back(std::chrono::milliseconds(45));
		std::vector<LPDIRECT3DTEXTURE9> texs;
		for (int i = 0; i < frames.size(); i++)
			texs.push_back(GUI::gui->LoadTexture(frames[i]));
		h.GetSprite()->Animations[string] = Animation(texs, aniDelays);
	}
	h.set_dest(-1, -1);
	h.set_exploded(false);
	h.set_time_left(5000);
	h.SetType(GameObjectType_Human);
	objects.push_back(std::make_shared<GameObject>(h));
	objects.back()->GetSprite()->StartAnimation("Foward");
}

void SpawnVFXBloodCloud(std::vector<std::shared_ptr<GameObject>>& objects, const int& x, const int& y, const int& width, const int& height) {
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
	objects.push_back(std::make_shared<GameObject>(explosion));
	objects.back()->GetSprite()->StartAnimation("default");
}

void SpawnVFXBloodClouds(std::vector<std::shared_ptr<GameObject>>& objects, const int& x, const int& y, const int& width, const int& height, const int& offsetPer = 2) {
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
	GameObject obj;
	Organ& organ = *reinterpret_cast<Organ*>(&obj);
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


// A utility function to format numbers like Egg Inc.
std::string formatNumber(const uint64_t& num) {
	if (num < 1000) {
		return std::to_string(num);
	}

	// Define the suffixes for large numbers
	static const std::vector<std::string> suffixes = { "", "K", "M", "B", "T", "Qa", "Qi", "Sx", "Sp", "Oc", "No", "Dc" };

	// Find the appropriate suffix
	const int exp = static_cast<int>(std::log10(num) / 3);
	const double base = num / std::pow(1000, exp);

	// Ensure the suffix index is within the bounds of the suffixes vector
	if (exp >= suffixes.size()) {
		return "Number too large";
	}

	// Format the number with the suffix
	char formatted[10];
	sprintf_s(formatted, sizeof(formatted), "%.2f%s", base, suffixes[exp].c_str());

	return std::string(formatted);
}

FloodVector2 generateBiasedCoordinate(FloodVector2 prev, int minX, int maxX, int minY, int maxY, float bias = 1.f, float strength = 10.f) {
	int deltaX = 0, deltaY = 0;
	do {
		deltaX = (std::rand() % 41) - 20; 
		deltaY = (std::rand() % 21) - 10; 
		
		if(std::rand() % 2 == 0)
			deltaY += (strength) * bias;  // bias towards bottom
	
	} while (prev.x + deltaX < minX || prev.x + deltaX > maxX ||
		prev.y + deltaY < minY || prev.y + deltaY > maxY);

	return { prev.x + deltaX, prev.y + deltaY };
}

float calculateAngle(FloodVector2 human, FloodVector2 target) {
	float deltaX = target.x - human.x;
	float deltaY = target.y - human.y;
	float angleInRadians = std::atan2(deltaY, deltaX);
	return angleInRadians * (180.0f / 3.1415926);;
}

inline void GameLoop(Game* game) {
	// Part 1 Logic
	//
	std::vector<std::shared_ptr<GameObject>>& objects = game->GetGameObjects();
	GameData* gameData = game->GetGameData();

	
	bool SpawnPress = Graphics::DrawTextureButton(L"resources/sprites/personicon.png", FloodGui::Context.Display.DisplaySize.x/2.f - 300 /2.f, FloodGui::Context.Display.DisplaySize.y - 150.f, 300,  100, FloodColor(241, 11, 13, 255), FloodGui::Context.Display.DisplaySize.x / 2.f - 300 / 2.f + 100, FloodGui::Context.Display.DisplaySize.y - 150.f, 100, 100);
	{
		if (SpawnPress && objects.size() <= 3) {
			SpawnHuman(objects, 500, 100, 80, 80);
		}
	}
	static std::chrono::milliseconds lastLoop = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	
	for (int j = 0; j < objects.size(); j++)
	{
		GameObject& obj = *objects[j];
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
						SpawnVFXBloodClouds(objects, pos.x, pos.y, (human->GetSprite()->bottom - human->GetSprite()->top) / 2, (human->GetSprite()->bottom - human->GetSprite()->top) / 2);
					#else
						SpawnVFXBloodCloud(objects, pos.x, pos.y, (human->GetSprite()->bottom - human->GetSprite()->top)/2, (human->GetSprite()->bottom - human->GetSprite()->top) / 2);
					#endif // ENHANCE_VFXBLOOD_CLOUDS
				
					HumanTypes type = (HumanTypes)human->nAttributes["type"];
				
					// SFX
					if(type == HumanType_Bert)
						soundSystem->PlayAudio(L"resources/sounds/music/BYEBYE.wav", .3f);
					else
						soundSystem->PlayAudio(L"resources/sounds/sfx/explosion.wav", .5f);


					Organ newOrgan = drop_new_organ(pos.x, pos.y, (human->GetSprite()->right - human->GetSprite()->left)/5, (human->GetSprite()->bottom - human->GetSprite()->top)/5);
					newOrgan.GetSprite()->texture = GUI::gui->LoadTexture(OrganTextures[(OrganTypes)newOrgan.nAttributes["type"]]);
					objects.push_back(std::make_shared<GameObject>(newOrgan));

					break;
				}
				else {
					// Make them run to a certian place!
					// use elapsed time to move them!
					
					if ((!human->GetSprite()->inAnimation || human->GetSprite()->animationFrame+1 == human->GetSprite()->Animations[human->GetSprite()->curAnimation].textures.size()) && human->GetSprite()->lastAnimation.length() > 1) {
						human->GetSprite()->StartAnimation(human->GetSprite()->lastAnimation);
					}else
						human->GetSprite()->UpdateAnimation();
					
					if (human->get_dest_x() < 0 && human->get_dest_y() < 0) {
						//  new destination 
						const FloodVector2& vec = generateBiasedCoordinate(
							{ static_cast<float>(human->GetSprite()->x), static_cast<float>(human->GetSprite()->y) },
							20, FloodGui::Context.Display.DisplaySize.x - 20,
							20, FloodGui::Context.Display.DisplaySize.y - 40,
							1.2f, 15.f
						);
						human->set_dest(vec.x, vec.y);

						float angleDeg = calculateAngle({ static_cast<float>(human->GetSprite()->x), static_cast<float>(human->GetSprite()->y) }, { static_cast<float>(human->get_dest_x()), static_cast<float>(human->get_dest_y()) });

						// Calculate Animations
						if (angleDeg >= 30 && angleDeg <= 60)
						{
							human->GetSprite()->StartAnimation("Seast");
						}
						else if (angleDeg > 60 && angleDeg < 120)
						{
							human->GetSprite()->StartAnimation("Foward");
						}else if (angleDeg >= 120 && angleDeg <= 150)
						{
							human->GetSprite()->StartAnimation("Sest");

						}
						else if (angleDeg > 150 && angleDeg < 210)
						{
							human->GetSprite()->StartAnimation("Left");

						}
						else if (angleDeg >= 210 && angleDeg <= 240)
						{
							human->GetSprite()->StartAnimation("Nest");

						}
						else if (angleDeg > 240 && angleDeg < 300)
						{
							human->GetSprite()->StartAnimation("Backward");

						}
						else if (angleDeg >= 300 && angleDeg <= 330)
						{
							human->GetSprite()->StartAnimation("Neast");

						}
						else
						{
							human->GetSprite()->StartAnimation("Right");
						}
					}
					else {
						int currentX = human->GetSprite()->x;
						int currentY = human->GetSprite()->y;
						int destX = human->get_dest_x();
						int destY = human->get_dest_y();


						// This needs to be improved
						int moveDst = ((FloodGui::Context.FrameData.tElaspedFrame.count()*1000.f) * 1.5f);

						if (currentX == destX && currentY == destY) {
							// reset to (-1, -1)
							human->set_dest(-1, -1);
						}
						else {
							// horizontally 
							if (currentX < destX) {
								human->SetPosition(currentX + min(moveDst, destX - currentX), currentY);
							}
							else if (currentX > destX) {
								human->SetPosition(currentX - min(moveDst,  currentX - destX ), currentY);
							}

							// vertically 
							if (currentY < destY) {
								human->SetPosition(human->GetSprite()->x, currentY + min(moveDst, destY - currentY));
							}
							else if (currentY > destY) {
								human->SetPosition(human->GetSprite()->x, currentY - min(moveDst, currentY - destY));
							}
						}
					}

				
					

					// count down till BYE BYE
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
						// Unused
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
					const float& wheighted = price * gameData->OrganCollectionMultiplyer.Value;

					gameData->Glorbux += wheighted;

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

				const int& xSpawn = livingspace->GetSprite()->left+(livingspace->GetSprite()->right - livingspace->GetSprite()->left)/2;
				const int& ySpawn = livingspace->GetSprite()->bottom;

				if (SpawnPress) {
					// While Button is held decrease curret_capacity - Spawm Humans

					if (livingspace->get_current_capacity() > 0) {
						SpawnHuman(objects, xSpawn, ySpawn, 70, 70);

						livingspace->set_current_capacity(livingspace->get_current_capacity() - 1);
					}
				}
				else {
					// While Button is not held refill current_capacity to full (at a rate)
					// utilize elapsed time
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
				GameObject& obj1 = *(objects[i - 1].get());
				GameObject& obj2 = *(objects[i].get());

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
	
	for (std::shared_ptr<GameObject> objj : objects) {
		GameObject& obj = *(objj.get());
		Sprite* sprite = obj.GetSprite();
		if (obj.GetType() == GameObjectType_None || !sprite->texture)
			continue;
		if (obj.GetType() == GameObjectType_Organ)
		{
			const float& bob = 2.f*sin(FloodGui::Context.FrameData.FrameCount*(.05));
			drawList->AddRectFilled(FloodVector2(sprite->left, sprite->top + bob), FloodVector2(sprite->right, sprite->bottom + bob), FloodColor(1.f, 1.f, 1.f), sprite->texture);
		}
		else {
			drawList->AddRectFilled(FloodVector2(sprite->left, sprite->top), FloodVector2(sprite->right, sprite->bottom), FloodColor(1.f, 1.f, 1.f), sprite->texture);
		}
	}

	// UI AT THE TOP
	{
		// Money
		{
			FloodVector2 glorbuxSize(50, 50);
			FloodVector2 moneyVec(50, 100);
			
			FloodVector2 topVec = moneyVec - (glorbuxSize / 2.f);
			FloodVector2 botVec = moneyVec + (glorbuxSize / 2.f);
			
			const std::string& money = formatNumber(gameData->Glorbux);

			Graphics::DrawUIElement(money.c_str(), 16, 16, moneyVec.x, moneyVec.y, glorbuxSize.x, glorbuxSize.y, FloodColor(1.f, 1.f, 1.f), L"resources/sprites/glorbuxicon.png");
		}

		// Upgrade Menu
		{
			static bool upgradeOpen = false;
			static const int& width = 50;
			static const int& height = 35;

			static const int& y = 100 - height / 2.f;
			static const int& x = FloodGui::Context.Display.DisplaySize.x - width - 30;

			if (!upgradeOpen)
			{	
				upgradeOpen = Graphics::DrawTextureButton(L"resources/sprites/threelinesicon.png", x, y, width, height, FloodColor(1.f, 1.f, 1.f), x+(15/2.f), y, width-15, height);
			}
			else {
				drawList->AddRectFilled({ FloodGui::Context.Display.DisplaySize.x - 300, static_cast<float>(y) }, FloodGui::Context.Display.DisplaySize - FloodVector2{0, static_cast<float>(y)}, FloodColor(1.f, 1.f, 1.f));
				if(Graphics::DrawTextureButton(L"resources/sprites/threelinesicon.png", FloodGui::Context.Display.DisplaySize.x - 300, y, width, height, FloodColor(1.f, 1.f, 1.f), FloodGui::Context.Display.DisplaySize.x  - 300 + (15 / 2.f), y, width - 15, height))
					upgradeOpen = false;
				drawList->AddText("Upgrades", { FloodGui::Context.Display.DisplaySize.x - 300 + (15 / 2.f) + width + 5, y + height - (height / 4.f) }, FloodColor(), 15, 15);
				// Loop through upgrades.

			}
		}
	}
	lastLoop = now;
}

Game::Game() {
	
}

Game::~Game() {
	GameObjects.clear();
}


// Upgrade Functions
void OrganCollectionMultiplyerHandle(void* gamePtr, void* ptr)
{
	Upgrade<float>* upgrade = reinterpret_cast<Upgrade<float>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);
	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 1.85;
		upgrade->Value *= 1.05;

	} else {
		// Nick will figure this out
	}
}
void OrganSpoilRate(void* gamePtr, void* ptr) {


	Upgrade<float>* upgrade = reinterpret_cast<Upgrade<float>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);


	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 1.85;
		upgrade->Value += 0.5; //Secounds

	} else {
		// Nick will figure this out
	}
}
//MAX LEVEL =2
void UFOCollectors(void* gamePtr, void* ptr) {


	Upgrade<int>* upgrade = reinterpret_cast<Upgrade<int>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);


	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 12.15;
		upgrade->Value += 1;

	} else {
		// Nick will figure this out
	}
}
//MAx level undetermand
void UFOSpeed(void* gamePtr, void* ptr)
{
	Upgrade<float>* upgrade = reinterpret_cast<Upgrade<float>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);
	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 3.14;
		upgrade->Value += 0.2f;

	} else {
		// Nick will figure this out
	}
}
//MAX Level==5
void UFORadius(void* gamePtr, void* ptr)
{
	Upgrade<float>* upgrade = reinterpret_cast<Upgrade<float>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);
	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 3.5;
		upgrade->Value += 0.5;

	} else {
		// Nick will figure this out
	}
}
//MAX level 5
void LivingSpaceUpgrades(void* gamePtr, void* ptr)
{
	Upgrade<byte>* upgrade = reinterpret_cast<Upgrade<byte>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);
	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 70;
		
	} else {
		// Nick will figure this out
	}
}
//Max Level == 5
void SpawnRate(void* gamePtr, void* ptr)
{
	Upgrade<float>* upgrade = reinterpret_cast<Upgrade<float>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);
	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 21;
		upgrade->Value += 1;

	} else {
		// Nick will figure this out
	}
}
//Constant == RefillRate
void LivingSpaceRefillRate(void* gamePtr, void* ptr)
{
	Upgrade<float>* upgrade = reinterpret_cast<Upgrade<float>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);
	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 1.5;
		upgrade->Value *= 0.95;

	} else {
		// Nick will figure this out
	}
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
		gameData.Glorbux = 20;
		
		for (int i = 0; i < 3; i++) {
			gameData.LivingSpaceUpgrades[i].upgradeName = "Living Space " + std::to_string(i);
			gameData.LivingSpaceUpgrades[i].nextLevelCost = 20;
			gameData.LivingSpaceUpgrades[i].level = 0;
			gameData.LivingSpaceUpgrades[i].levelMax = LivingSpaceNames.size() - 1;
		}
		gameData.OrganCollectionMultiplyer.upgradeName = "Organ Collection Multiplyer";
		gameData.OrganCollectionMultiplyer.nextLevelCost = 100;
		gameData.OrganCollectionMultiplyer.upgradeHandle = (upgrade_handle_fn)OrganCollectionMultiplyerHandle;
		gameData.OrganCollectionMultiplyer.level = 0;
		gameData.OrganCollectionMultiplyer.levelMax = 100;
		gameData.OrganCollectionMultiplyer.Value = 1;

	}

	std::srand(time(NULL));
}

void Game::InitalizeGameSound() {
	soundSystem = new SoundSystem();
	soundSystem->Init();
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

std::vector<std::shared_ptr<GameObject>>& Game::GetGameObjects() { return GameObjects; }

GameData* Game::GetGameData() { return &gameData; }