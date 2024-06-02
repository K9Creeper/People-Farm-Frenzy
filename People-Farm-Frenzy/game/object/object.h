#pragma once
#include <cstdint>
#include <unordered_map>

#include "../graphics/sprite/sprite.h"

enum GameObjectType : uint16_t {
	GameObjectType_None = 0,
	GameObjectType_VFXEnviorment,
	GameObjectType_Human,
	GameObjectType_Organ,
	GameObjectType_LivingSpace,
	GameObjectType_UFOCollector,
	GameObjectType_VFX,
};

// Game Object ;)
class GameObject {
public:
	GameObject(){ }
	~GameObject(){
		nAttributes.clear();
		sAttributes.clear();
	}
private:
	GameObjectType type = GameObjectType_None;

	Sprite sprite;
public:
	// This will contain string information about object attributes
	std::unordered_map<std::string, std::string>sAttributes{};
	// This will contain numerical information about object attributes
	std::unordered_map<std::string, double>nAttributes{};

	GameObjectType GetType()const;
	void SetType(GameObjectType type);
	Sprite* GetSprite();

	void SetSize(const int& width, const int& height);
	void SetPosition(const int& x, const int& y);
};