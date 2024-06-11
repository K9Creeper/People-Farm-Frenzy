#include "game.h"

#include "../gui/gui.h"
#include "../gui/window/window.h"

#include "graphics/interact/interact.h"
#include "soundsystem/soundsystem.h"

#include <iostream>

constexpr float GAMESCALEX();
constexpr float GAMESCALEY();

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


void AddLivingSpace(std::vector<std::shared_ptr<GameObject>>& objects, const int& slot, LivingSpaceTypes type, const int& capacity) {
	static const float scaleX = GAMESCALEX();
	static const float scaleY = GAMESCALEY();
	
	LivingSpace h;
	h.SetType(GameObjectType_LivingSpace);

	int positionX = LivingSpaceSlotInfos[slot].x * scaleX;

	float width = LivingSpaceSlotInfos[slot].width * scaleX + (scaleX * 2);
	float height = LivingSpaceSlotInfos[slot].height * scaleY + (scaleY * 2);

	h.SetSize(width, height);
	h.SetPosition(positionX + width/2.f, 0 + height/2.f);
	h.nAttributes["slot"] = slot;
	h.nAttributes["type"] = type;

	if(type != LivingSpaceType_None)
		h.GetSprite()->texture = GUI::gui->LoadTexture(LivingSpaceTextures[type]);

	h.set_current_capacity(min(capacity, h.get_max_capacity()));

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetType() != GameObjectType_LivingSpace)
			continue;
		LivingSpace* h = reinterpret_cast<LivingSpace*>(objects[i].get());
		if (h->get_slot() == slot)
		{
			objects.erase(objects.begin() + i);
			break;
		}
	}

	objects.push_back(std::make_shared<GameObject>(h));
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

Organ drop_new_organ(Game* game, const int& x, const int& y, const int& width, const int& height) {
	double random = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	GameObject obj;
	Organ& organ = *reinterpret_cast<Organ*>(&obj);
	organ.SetType(GameObjectType_Organ);
	double Chance = 1.f;

	// convert sec to milli
	organ.set_time_left(game->GetGameData()->OrganSpoilRate.Value * 1000.f);

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

FloodVector2 generateBiasedCoordinate(const FloodVector2& prev, const int& minX, const int& maxX, const int&  minY, const int& maxY, const float& bias = 1.f, const float& strength = 10.f) {
	int deltaX = 0, deltaY = 0;
	do {
		// not move more than 20 pixels
		deltaX = (std::rand() % 41) - 20; // This is from -20 to 20 range
		deltaY = (std::rand() % 21) - 10;// this allos travle from -10 to 10
										 // bias towards bottom
		
		if(std::rand() % 2 == 0)
			deltaY += (strength) * bias;  // further bias towards bottom
	
	} while (prev.x + deltaX < minX || prev.x + deltaX > maxX ||
		prev.y + deltaY < minY || prev.y + deltaY > maxY);

	return { prev.x + deltaX, prev.y + deltaY };
}

float calculateAngle(const FloodVector2& human, const FloodVector2& target) {
	float deltaX = target.x - human.x;
	float deltaY = target.y - human.y;

	float angleInRadians = std::atan2(deltaY, deltaX);
	
	return angleInRadians * (180.0f / 3.1415926);;
}

constexpr float GAMESCALEX()
{
	return FloodGui::Context.Display.DisplaySize.x / 1280;
}

constexpr float GAMESCALEY()
{
	return FloodGui::Context.Display.DisplaySize.y / 720;
}

inline void GameLoop(Game* game) {
	// Part 1 Logic
	//
	std::vector<std::shared_ptr<GameObject>>& objects = game->GetGameObjects();
	GameData* gameData = game->GetGameData();

	
	bool SpawnPress = Graphics::DrawTextureButton(L"resources/sprites/personicon.png", FloodGui::Context.Display.DisplaySize.x/2.f - (300*GAMESCALEX()) /2.f, FloodGui::Context.Display.DisplaySize.y - 150.f* GAMESCALEY(), 300* GAMESCALEX(),  100*GAMESCALEY(), FloodColor(241, 11, 13, 255), FloodGui::Context.Display.DisplaySize.x / 2.f - (300* GAMESCALEX()) / 2.f + (100* GAMESCALEX()), FloodGui::Context.Display.DisplaySize.y - (150.f * GAMESCALEY()), 100 * GAMESCALEX(), 100 * GAMESCALEY());

	static std::chrono::milliseconds last_press = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	static std::chrono::milliseconds last_spawned= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	static std::chrono::milliseconds last_refill = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	if (SpawnPress) {
			last_press = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	}

	static std::chrono::milliseconds lastLoop = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	
	bool spawnedSomething = false;
	bool refilledSomething = false;

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


					Organ newOrgan = drop_new_organ(game, pos.x, pos.y, (human->GetSprite()->right - human->GetSprite()->left)/4, (human->GetSprite()->bottom - human->GetSprite()->top)/4);
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
							40*GAMESCALEX(), FloodGui::Context.Display.DisplaySize.x - 40 * GAMESCALEX(),
							39 * GAMESCALEY(), FloodGui::Context.Display.DisplaySize.y - 95 * GAMESCALEY(),
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
						int moveDst = 1;

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
					break;
				}
				if(organ->get_time_left() <= 0) {
					objects.erase(objects.begin() + j);
					break;
				}

				organ->set_time_left(organ->get_time_left() - ((now - lastLoop).count()));
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
					if (livingspace->get_current_capacity() > 0 && ((last_spawned.count() + (long long)gameData->SpawnRate.Value) <= (now).count())) {
						SpawnHuman(objects, xSpawn, ySpawn, 90 * GAMESCALEX(), 90 * GAMESCALEY());
						spawnedSomething = true;
						livingspace->set_current_capacity(livingspace->get_current_capacity() - 1);
					}
				}
				else {
					if (livingspace->get_current_capacity() < livingspace->get_max_capacity())
					{
						if ((last_refill.count() + (long long)gameData->LivingSpaceRefillRate.Value) <= (now).count())
						{
							refilledSomething = true;
							livingspace->set_current_capacity(livingspace->get_current_capacity() + 1);
						}
					}
					
				
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
	if(spawnedSomething)
		last_spawned = now;
	if (refilledSomething)
		last_refill = now;
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
		else if (obj.GetType() == GameObjectType_LivingSpace)
		{
			LivingSpace* s = reinterpret_cast<LivingSpace*>(objj.get());
			drawList->AddRectFilled(FloodVector2(sprite->left, sprite->top), FloodVector2(sprite->right, sprite->bottom), FloodColor(1.f, 1.f, 1.f), sprite->texture);
			drawList->AddText(std::to_string(s->get_current_capacity()).c_str(), FloodVector2(sprite->left, sprite->bottom - ((sprite->bottom - sprite->top)/4.f)), FloodColor(1.f, 1.f, 1.f), 15 * GAMESCALEY(), 15 * GAMESCALEX());
		}
		else {
			drawList->AddRectFilled(FloodVector2(sprite->left, sprite->top), FloodVector2(sprite->right, sprite->bottom), FloodColor(1.f, 1.f, 1.f), sprite->texture);
		}
	}

	// UI AT THE TOP
	{
		// Money
		{
			FloodVector2 glorbuxSize(50* GAMESCALEX(), 50 * GAMESCALEY());
			FloodVector2 moneyVec(50 * GAMESCALEX(), 100 * GAMESCALEY());
			
			FloodVector2 topVec = moneyVec - (glorbuxSize / 2.f);
			FloodVector2 botVec = moneyVec + (glorbuxSize / 2.f);
			
			const std::string& money = formatNumber(gameData->Glorbux);

			Graphics::DrawUIElement(money.c_str(), 16 * GAMESCALEY(), 16 * GAMESCALEX(), moneyVec.x, moneyVec.y, glorbuxSize.x, glorbuxSize.y, FloodColor(1.f, 1.f, 1.f), L"resources/sprites/glorbuxicon.png");
		}

		// Upgrade Menu
		{
			static bool up = true;
			static bool upgradeOpen = false;

			static const float& width = 50 * GAMESCALEX();
			static const float& height = 35 * GAMESCALEY();

			static const float& y = 100 * GAMESCALEY() - height / 2.f;
			static const float& x = FloodGui::Context.Display.DisplaySize.x - width - 30 * GAMESCALEX();

			Graphics::DrawTextureButton(L"resources/sprites/threelinesicon.png", x, y, width, height, FloodGui::Context.colors[FloodGuiCol_WinTitleBar], x+(15 * GAMESCALEX() /2.f), y, width-(15 * GAMESCALEY()), height);
			if (up && FloodGui::Context.IO.MouseInput[FloodGuiButton_LeftMouse] && FindPoint( { x, y }, { x + width, y + height }, FloodGui::Context.IO.mouse_pos))
			{
				up = false;
				upgradeOpen = !upgradeOpen;
			}
			else if (!FloodGui::Context.IO.MouseInput[FloodGuiButton_LeftMouse])
				up = true;
			else if (FloodGui::Context.IO.MouseInput[FloodGuiButton_LeftMouse])
				up = false;
			

			FloodGui::BeginWindow("Upgrades", upgradeOpen);
			for (int i = 0; i < 3; i++) {
					std::string price = (formatNumber(gameData->LivingSpaceUpgrades[i].nextLevelCost) + " Glorbux");
					std::string name = gameData->LivingSpaceUpgrades[i].upgradeName + " Lvl. " + std::to_string(gameData->LivingSpaceUpgrades[i].level) + " of " + std::to_string(gameData->LivingSpaceUpgrades[i].levelMax);
					name += "  " + price;
					if (FloodGui::Button(name.c_str()))
					{
						gameData->LivingSpaceUpgrades[i].upgradeHandle(game, &gameData->LivingSpaceUpgrades[i]);
						AddLivingSpace(objects, i + 1, (LivingSpaceTypes)gameData->LivingSpaceUpgrades[i].level, 1000000);
					}
			}
			{
				std::string price = (formatNumber(gameData->OrganCollectionMultiplyer.nextLevelCost) + " Glorbux");			
				std::string name = gameData->OrganCollectionMultiplyer.upgradeName + " Lvl. " + std::to_string(gameData->OrganCollectionMultiplyer.level) + " of " + std::to_string(gameData->OrganCollectionMultiplyer.levelMax);
				name += "  " + price;
				if (FloodGui::Button(name.c_str()))
				{
					gameData->OrganCollectionMultiplyer.upgradeHandle(game, &gameData->OrganCollectionMultiplyer);
				}
			}
			{
				std::string price = (formatNumber(gameData->OrganSpoilRate.nextLevelCost) + " Glorbux");
				std::string name = gameData->OrganSpoilRate.upgradeName + " Lvl. " + std::to_string(gameData->OrganSpoilRate.level) + " of " + std::to_string(gameData->OrganSpoilRate.levelMax);
				name += "  " + price;
				if (FloodGui::Button(name.c_str()))
				{
					gameData->OrganSpoilRate.upgradeHandle(game, &gameData->OrganSpoilRate);
				}
			}
			{
				std::string price = (formatNumber(gameData->SpawnRate.nextLevelCost) + " Glorbux");
				std::string name = gameData->SpawnRate.upgradeName + " Lvl. " + std::to_string(gameData->SpawnRate.level) + " of " + std::to_string(gameData->SpawnRate.levelMax);
				name += "  " + price;
				if (FloodGui::Button(name.c_str()))
				{
					gameData->SpawnRate.upgradeHandle(game, &gameData->SpawnRate);
				}
			}
			{
				std::string price = (formatNumber(gameData->LivingSpaceRefillRate.nextLevelCost) + " Glorbux");
				std::string name = gameData->LivingSpaceRefillRate.upgradeName + " Lvl. " + std::to_string(gameData->LivingSpaceRefillRate.level) + " of " + std::to_string(gameData->LivingSpaceRefillRate.levelMax);
				name += "  " + price;
				if (FloodGui::Button(name.c_str()))
				{
					gameData->LivingSpaceRefillRate.upgradeHandle(game, &gameData->LivingSpaceRefillRate);
				}
			}
			FloodGui::EndWindow();
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
void OrganCollectionMultiplyerUpgrade(void* gamePtr, void* ptr)
{
	Upgrade<float>* upgrade = reinterpret_cast<Upgrade<float>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);
	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 3;
		upgrade->Value *= 1.5;

	} else {
		// Nick will figure this out
	}
}
void OrganSpoilRateUpgrade(void* gamePtr, void* ptr) {


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
void UFOSpeedUpgrade(void* gamePtr, void* ptr)
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
void UFORadiusUpgrade(void* gamePtr, void* ptr)
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

void LivingSpaceUpgrades(void* gamePtr, void* ptr)
{
	Upgrade<byte>* upgrade = reinterpret_cast<Upgrade<byte>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);
	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 3;

	} else {
		// Nick will figure this out

	}
}
//Max Level == 5
void SpawnRateUpgrade(void* gamePtr, void* ptr)
{
	Upgrade<float>* upgrade = reinterpret_cast<Upgrade<float>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);
	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 1.7;
		upgrade->Value *= .70;

	} else {
		// Nick will figure this out
	}
}
//Constant == RefillRate
void LivingSpaceRefillRateUpgrade(void* gamePtr, void* ptr)
{
	Upgrade<float>* upgrade = reinterpret_cast<Upgrade<float>*>(ptr);
	Game* game = reinterpret_cast<Game*>(gamePtr);
	if ((game->GetGameData()->Glorbux >= upgrade->nextLevelCost) && (upgrade->level < upgrade->levelMax)) {
		game->GetGameData()->Glorbux -= upgrade->nextLevelCost;
		upgrade->level += 1;
		upgrade->nextLevelCost *= 1.5;
		upgrade->Value *= 0.75;

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
			gameData.LivingSpaceUpgrades[i].upgradeName = "House " + std::to_string(i+1);
			gameData.LivingSpaceUpgrades[i].nextLevelCost = 20;
			gameData.LivingSpaceUpgrades[i].level = 0;
			gameData.LivingSpaceUpgrades[i].levelMax = LivingSpaceNames.size() - 1;
			gameData.LivingSpaceUpgrades[i].upgradeHandle = (upgrade_handle_fn)LivingSpaceUpgrades;
		}
		{
			gameData.OrganCollectionMultiplyer.upgradeName = "Organ Multi.";
			gameData.OrganCollectionMultiplyer.nextLevelCost = 900;
			gameData.OrganCollectionMultiplyer.upgradeHandle = (upgrade_handle_fn)OrganCollectionMultiplyerUpgrade;
			gameData.OrganCollectionMultiplyer.level = 0;
			gameData.OrganCollectionMultiplyer.levelMax = 5;
		}
		{
			gameData.OrganSpoilRate.upgradeName = "Organ Spoil";
			gameData.OrganSpoilRate.nextLevelCost = 100;
			gameData.OrganSpoilRate.upgradeHandle = (upgrade_handle_fn)OrganSpoilRateUpgrade;
			gameData.OrganSpoilRate.level = 0;
			gameData.OrganSpoilRate.levelMax = 10;
		}
		{
			gameData.LivingSpaceRefillRate.upgradeName = "Refill Rate";
			gameData.LivingSpaceRefillRate.nextLevelCost = 1000;
			gameData.LivingSpaceRefillRate.upgradeHandle = (upgrade_handle_fn)LivingSpaceRefillRateUpgrade;
			gameData.LivingSpaceRefillRate.level = 0;
			gameData.LivingSpaceRefillRate.levelMax = 5;
		}
		{
			gameData.SpawnRate.upgradeName = "Spawn Rate";
			gameData.SpawnRate.nextLevelCost = 500;
			gameData.SpawnRate.upgradeHandle = (upgrade_handle_fn)SpawnRateUpgrade;
			gameData.SpawnRate.level = 0;
			gameData.SpawnRate.levelMax = 5;
		}
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

	soundSystem->PlayAudio(L"resources/sounds/music/black-hawk-light-cinematic-background-music-for-drama-video-40-second-202452.wav", .15f, true);

	GUI::gui->RunFlood();
}

std::vector<std::shared_ptr<GameObject>>& Game::GetGameObjects() { return GameObjects; }

GameData* Game::GetGameData() { return &gameData; }