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
	void set_exploded() { nAttributes["exploded"] = true; }
	Organ drop_new_organ() {
		const double& random = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

		Organ organ;
		if (random <= OrganChances[OrganType_Bone])
			organ.nAttributes["type"] = OrganType_Bone;
		if (random <= OrganChances[OrganType_Skin])
			organ.nAttributes["type"] = OrganType_Skin;
		if (random <= OrganChances[OrganType_Stomach])
			organ.nAttributes["type"] = OrganType_Stomach;
		if (random <= OrganChances[OrganType_Intestine])
			organ.nAttributes["type"] = OrganType_Intestine;
		if (random <= OrganChances[OrganType_Eyeball])
			organ.nAttributes["type"] = OrganType_Eyeball;
		if (random <= OrganChances[OrganType_Kidney])
			organ.nAttributes["type"] = OrganType_Kidney;
		if (random <= OrganChances[OrganType_Lung])
			organ.nAttributes["type"] = OrganType_Lung;
		if (random <= OrganChances[OrganType_Heart])
			organ.nAttributes["type"] = OrganType_Heart;
		if (random <= OrganChances[OrganType_Brain])
			organ.nAttributes["type"] = OrganType_Brain;
        
		// Lol who cares about effi.
		organ.SetSize(50, 50);
		organ.SetPosition(GetSprite()->x, GetSprite()->y);
		organ.SetType(GameObjectType_Organ);
		
		organ.nAttributes["value"] = OrganValues[(OrganTypes)organ.nAttributes["type"]];
		organ.sAttributes["name"] = OrganNames[(OrganTypes)organ.nAttributes["type"]];
		

		return organ;
	}
};