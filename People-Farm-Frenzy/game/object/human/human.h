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

static std::unordered_map<HumanTypes, LPCWSTR>HumanTextures{
	// NUM								SRC
	{HumanType_Bert,					L"resources/sprites/SpriteTest.jpg" },
	{HumanType_Boy1,					L"resources/sprites/SpriteTest.jpg"},
	{HumanType_Boy2,					L"resources/sprites/SpriteTest.jpg" },
	{HumanType_Boy3,					L"resources/sprites/SpriteTest.jpg"},
	{HumanType_Girl1,					L"resources/sprites/SpriteTest.jpg" },
	{HumanType_Girl2,					L"resources/sprites/SpriteTest.jpg" },
};

static std::unordered_map <HumanTypes, double>HumanChances{
	// NUM				CHANCE
	{HumanType_Bert,		1.f / 250.f},
	{HumanType_Boy1 ,		19.8f / 100.f},
	{HumanType_Boy2 ,		19.8f / 100.f},
	{HumanType_Boy3 ,		19.8f / 100.f},
	{HumanType_Girl1 ,		19.8f / 100.f},
	{HumanType_Girl2 ,		19.8f / 100.f }
};

static std::unordered_map<HumanTypes, std::unordered_map<std::string, std::vector<LPCWSTR>>>HumanAnimations{
	{ 
		HumanType_Bert, 
		{
			{"Foward", {}},
			{"Right", {}},
			{"Backward", {}},
			{"Left", {}},
			{"Neast", {}},
			{"Seast", {}},
			{"Nest", {}},
			{"Sest", {}},
		} 
	},
};


class Human : public GameObject {
public:
	int get_time_left() { return nAttributes["time_left"]; }
	void set_time_left(const int& time) { nAttributes["time_left"] = time; }
	bool get_exploded() { return nAttributes["exploded"]; }
	void set_exploded(bool b = true) { nAttributes["exploded"] = b; }
	int get_dest_x() { return nAttributes["dest_x"]; };
	int get_dest_y() { return nAttributes["dest_y"]; };
	void set_dest(const int& x, const int& y) {
		nAttributes["dest_x"] = x;
		nAttributes["dest_y"] = y;
	}
	HumanTypes get_human_type() { return (HumanTypes)static_cast<int>(nAttributes["type"]); }
};