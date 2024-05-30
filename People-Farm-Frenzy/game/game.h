#pragma once
#include "object/object.h"
#include "object/human/human.h"
#include "object/organ/organ.h"
#include "object/livingspace/livingspace.h"
#include "object/UFO/UFO.h"

struct GameData {

};

class Game {
public:
	Game();
	~Game();
private:
	std::vector<GameObject>GameObjects{};

	GameData gameData;
public:

};

inline void GameLoop(Game* game);