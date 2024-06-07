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

enum HumanTypes : uint16_t {
	HumanType_Bert = 0,
	HumanType_Boy1,
	HumanType_Boy2,
	HumanType_Boy3,
	HumanType_Girl1,
	HumanType_Girl2
};

static std::unordered_map<HumanTypes, std::vector<LPCWSTR>>HumanTextures{
	// NUM						SRC
	{HumanType_Bert,					{ L"c3949d6b-0202-4c4d-a703-155a46218b87-0.png"}},
	{HumanType_Boy1,					{ L"resources/sprites/SpriteTest.jpg" } },
	{HumanType_Boy2,					{ L"resources/sprites/SpriteTest.jpg" } },
	{HumanType_Boy3,					{ L"resources/sprites/SpriteTest.jpg" }},
	{HumanType_Girl1,					{ L"resources/sprites/SpriteTest.jpg" } },
	{HumanType_Girl2,					{ L"resources/sprites/SpriteTest.jpg" } },
};



class Human : public GameObject {
public:
	int get_time_left() { return nAttributes["time_left"]; }
	void set_time_left(const int& time) { nAttributes["time_left"] = time; }
	bool get_exploded() { return nAttributes["exploded"]; }
	void set_exploded(bool b = true) { nAttributes["exploded"] = b; }
	void set_human_type(const HumanTypes& type) { nAttributes["human_type"] = type; }
	HumanTypes get_human_type() { return (HumanTypes)static_cast<int>(nAttributes["human_type"]); }
};