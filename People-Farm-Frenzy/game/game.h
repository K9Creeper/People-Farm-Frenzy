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

//#define ENHANCE_VFXBLOOD_CLOUDS

static std::vector<LPCWSTR>BackgroundFrames{
	L"resources/sprites/map/map.png"
};

struct GameData {
	uint64_t Glorbux = 0;

	// So basically, they don't need to hold another obj.
	Upgrade<byte> LivingSpaceUpgrades[3]{ };
	
	Upgrade<float> OrganCollectionMultiplyer{ 1.0 };

	Upgrade<float> LivingSpaceRefillRate{ 1000.0 };
	Upgrade<int> UFOCollectors{ 0 };

	Upgrade<float>UFOSpeed{1};

	Upgrade<float>UFORadius{1};
	Upgrade<float>SpawnRate{1000.f};
	Upgrade<float>OrganSpoilRate{3};	
};

class Game {
public:
	Game();
	~Game();
private:
	std::vector<std::shared_ptr<GameObject>>GameObjects{};

	GameData gameData;
public:
	void InitalizeGameData();
	void InitalizeGameGraphics();
	void InitalizeGameSound();

	std::vector<std::shared_ptr<GameObject>>& GetGameObjects();
	GameData* GetGameData();
};

inline void GameLoop(Game* game);