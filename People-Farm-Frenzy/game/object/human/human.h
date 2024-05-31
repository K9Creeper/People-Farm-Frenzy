#pragma once
#include <cstring>

#include <random>
#include <ctime>

#include "../object.h"
#include "../organ/organ.h"

/*
Todo:
	1. Create a unordered_map of textures for each human
*/

static std::unordered_map<int, LPCWSTR>HumanTextures{
	// NUM				SRC
	{1,					L"resources/sprites/SpriteTest.jpg"},
	{2,					L"resources/sprites/SpriteTest.jpg" },
	{3,					L"resources/sprites/SpriteTest.jpg" }
};

class Human : public GameObject {
public:
	int get_time_left() { return nAttributes["time_left"]; }
	void set_time_left(const int& time) { nAttributes["time_left"] = time; }
	bool get_exploded() { return nAttributes["exploded"]; }
	void set_exploded(bool b = true) { nAttributes["exploded"] = b; }
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
			organ.nAttributes["type"] = OrganType_Bone;
		}
		Chance -= OrganChances[OrganType_Bone];

		organ.SetSize(width, height);
		organ.SetPosition(x, y);
		
		organ.nAttributes["value"] = OrganValues[(OrganTypes)organ.nAttributes["type"]];
		organ.sAttributes["name"] = OrganNames[(OrganTypes)organ.nAttributes["type"]];
		
		return organ;
	}
};