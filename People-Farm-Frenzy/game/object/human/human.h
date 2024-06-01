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
};