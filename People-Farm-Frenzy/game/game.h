#pragma once
#include "graphics/upgrade/upgrade.h"
#include "graphics/animation/animation.h"
#include "graphics/sprite/sprite.h"

#include "object/object.h"
#include "object/human/human.h"
#include "object/organ/organ.h"
#include "object/livingspace/livingspace.h"
#include "object/UFO/UFO.h"
#include "object/vfx/vfx.h"

static std::vector<LPCWSTR>BackgroundFrames{
	L"resources/sprites/map/map_0.png", L"resources/sprites/map/map_1.png", L"resources/sprites/map/map_2.png", L"resources/sprites/map/map_3.png",

};

struct GameData {
	uint64_t Glorbux = 0;

	Upgrade<LivingSpace> LivingSpaceUpgrades[4]{ };
	
	Upgrade<double> ButtonMultiplier{ 1.0 };
	Upgrade<double> LivingSpaceRefillMultiplier{ 1.0 };
	Upgrade<int> UFOCollectors{ 0 };
};

class Game {
public:
	Game();
	~Game();
private:
	std::vector<GameObject>GameObjects{};

	GameData gameData;
public:
	void InitalizeGameData();
	void InitalizeGameGraphics();

	std::vector<GameObject>& GetGameObjects();
};

inline void GameLoop(Game* game);