#pragma once
#include "graphics/upgrade/upgrade.h"
#include "graphics/animation/animation.h"
#include "graphics/sprite/sprite.h"

#include "object/object.h"
#include "object/human/human.h"
#include "object/organ/organ.h"
#include "object/livingspace/livingspace.h"
#include "object/UFO/UFO.h"

struct GameData {
	uint64_t Glorbux = 0;

	Upgrade<LivingSpace> LivingSpaceUpgrades[4]{ };
	
	Upgrade<double> ButtonMultiplier{ 1.0 };
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
};

inline void GameLoop(Game* game);