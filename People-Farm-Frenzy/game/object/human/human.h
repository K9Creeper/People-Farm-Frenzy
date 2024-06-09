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
	{HumanType_Bert,					L"resources/sprites/people/bert/frame (1).png" },
	{HumanType_Boy1,					L"resources/sprites/people/boy1/frame (1).png"},
	{HumanType_Boy2,					L"resources/sprites/people/boy2/frame (1).png" },
	{HumanType_Boy3,					L"resources/sprites/people/boy3/frame (1).png"},
	{HumanType_Girl1,					L"resources/sprites/people/girl1/frame (1).png" },
	{HumanType_Girl2,					L"resources/sprites/people/girl2/frame (1).png" },
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
			{"Foward", {L"resources/sprites/people/bert/frame (1).png", L"resources/sprites/people/bert/frame (2).png", L"resources/sprites/people/bert/frame (3).png", L"resources/sprites/people/bert/frame (4).png"}},
			{"Seast", {L"resources/sprites/people/bert/frame (5).png", L"resources/sprites/people/bert/frame (6).png", L"resources/sprites/people/bert/frame (7).png", L"resources/sprites/people/bert/frame (8).png"}},
			{"Right", {L"resources/sprites/people/bert/frame (9).png", L"resources/sprites/people/bert/frame (10).png", L"resources/sprites/people/bert/frame (11).png", L"resources/sprites/people/bert/frame (12).png"}},
			{"Neast", {L"resources/sprites/people/bert/frame (13).png", L"resources/sprites/people/bert/frame (14).png", L"resources/sprites/people/bert/frame (15).png", L"resources/sprites/people/bert/frame (16).png"}},
			{"Backward", {L"resources/sprites/people/bert/frame (17).png", L"resources/sprites/people/bert/frame (18).png", L"resources/sprites/people/bert/frame (19).png", L"resources/sprites/people/bert/frame (20).png"}},
			{"Nest", {L"resources/sprites/people/bert/frame (21).png", L"resources/sprites/people/bert/frame (22).png", L"resources/sprites/people/bert/frame (23).png", L"resources/sprites/people/bert/frame (24).png"}},
			{"Left", {L"resources/sprites/people/bert/frame (25).png", L"resources/sprites/people/bert/frame (26).png", L"resources/sprites/people/bert/frame (27).png", L"resources/sprites/people/bert/frame (28).png"}},
			{"Sest", {L"resources/sprites/people/bert/frame (29).png", L"resources/sprites/people/bert/frame (30).png", L"resources/sprites/people/bert/frame (31).png", L"resources/sprites/people/bert/frame (32).png"}},
		} 
	},
	{
		HumanType_Boy1,
		{
			{"Foward", {L"resources/sprites/people/boy1/frame (1).png", L"resources/sprites/people/boy1/frame (2).png", L"resources/sprites/people/boy1/frame (3).png", L"resources/sprites/people/boy1/frame (4).png"}},
			{"Seast", {L"resources/sprites/people/boy1/frame (5).png", L"resources/sprites/people/boy1/frame (6).png", L"resources/sprites/people/boy1/frame (7).png", L"resources/sprites/people/boy1/frame (8).png"}},
			{"Right", {L"resources/sprites/people/boy1/frame (9).png", L"resources/sprites/people/boy1/frame (10).png", L"resources/sprites/people/boy1/frame (11).png", L"resources/sprites/people/boy1/frame (12).png"}},
			{"Neast", {L"resources/sprites/people/boy1/frame (13).png", L"resources/sprites/people/boy1/frame (14).png", L"resources/sprites/people/boy1/frame (15).png", L"resources/sprites/people/boy1/frame (16).png"}},
			{"Backward", {L"resources/sprites/people/boy1/frame (17).png", L"resources/sprites/people/boy1/frame (18).png", L"resources/sprites/people/boy1/frame (19).png", L"resources/sprites/people/boy1/frame (20).png"}},
			{"Nest", {L"resources/sprites/people/boy1/frame (21).png", L"resources/sprites/people/boy1/frame (22).png", L"resources/sprites/people/boy1/frame (23).png", L"resources/sprites/people/boy1/frame (24).png"}},
			{"Left", {L"resources/sprites/people/boy1/frame (25).png", L"resources/sprites/people/boy1/frame (26).png", L"resources/sprites/people/boy1/frame (27).png", L"resources/sprites/people/boy1/frame (28).png"}},
			{"Sest", {L"resources/sprites/people/boy1/frame (29).png", L"resources/sprites/people/boy1/frame (30).png", L"resources/sprites/people/boy1/frame (31).png", L"resources/sprites/people/boy1/frame (32).png"}},
		}
	},
	{
		HumanType_Boy2,
		{
			{"Foward", {L"resources/sprites/people/boy2/frame (1).png", L"resources/sprites/people/boy2/frame (2).png", L"resources/sprites/people/boy2/frame (3).png", L"resources/sprites/people/boy2/frame (4).png"}},
			{"Seast", {L"resources/sprites/people/boy2/frame (5).png", L"resources/sprites/people/boy2/frame (6).png", L"resources/sprites/people/boy2/frame (7).png", L"resources/sprites/people/boy2/frame (8).png"}},
			{"Right", {L"resources/sprites/people/boy2/frame (9).png", L"resources/sprites/people/boy2/frame (10).png", L"resources/sprites/people/boy2/frame (11).png", L"resources/sprites/people/boy2/frame (12).png"}},
			{"Neast", {L"resources/sprites/people/boy2/frame (13).png", L"resources/sprites/people/boy2/frame (14).png", L"resources/sprites/people/boy2/frame (15).png", L"resources/sprites/people/boy2/frame (16).png"}},
			{"Backward", {L"resources/sprites/people/boy2/frame (17).png", L"resources/sprites/people/boy2/frame (18).png", L"resources/sprites/people/boy2/frame (19).png", L"resources/sprites/people/boy2/frame (20).png"}},
			{"Nest", {L"resources/sprites/people/boy2/frame (21).png", L"resources/sprites/people/boy2/frame (22).png", L"resources/sprites/people/boy2/frame (23).png", L"resources/sprites/people/boy2/frame (24).png"}},
			{"Left", {L"resources/sprites/people/boy2/frame (25).png", L"resources/sprites/people/boy2/frame (26).png", L"resources/sprites/people/boy2/frame (27).png", L"resources/sprites/people/boy2/frame (28).png"}},
			{"Sest", {L"resources/sprites/people/boy2/frame (29).png", L"resources/sprites/people/boy2/frame (30).png", L"resources/sprites/people/boy2/frame (31).png", L"resources/sprites/people/boy2/frame (32).png"}},
		}
	},
	{
		HumanType_Boy3,
		{
			{"Foward", {L"resources/sprites/people/boy3/frame (1).png", L"resources/sprites/people/boy3/frame (2).png", L"resources/sprites/people/boy3/frame (3).png", L"resources/sprites/people/boy3/frame (4).png"}},
			{"Seast", {L"resources/sprites/people/boy3/frame (5).png", L"resources/sprites/people/boy3/frame (6).png", L"resources/sprites/people/boy3/frame (7).png", L"resources/sprites/people/boy3/frame (8).png"}},
			{"Right", {L"resources/sprites/people/boy3/frame (9).png", L"resources/sprites/people/boy3/frame (10).png", L"resources/sprites/people/boy3/frame (11).png", L"resources/sprites/people/boy3/frame (12).png"}},
			{"Neast", {L"resources/sprites/people/boy3/frame (13).png", L"resources/sprites/people/boy3/frame (14).png", L"resources/sprites/people/boy3/frame (15).png", L"resources/sprites/people/boy3/frame (16).png"}},
			{"Backward", {L"resources/sprites/people/boy3/frame (17).png", L"resources/sprites/people/boy3/frame (18).png", L"resources/sprites/people/boy3/frame (19).png", L"resources/sprites/people/boy3/frame (20).png"}},
			{"Nest", {L"resources/sprites/people/boy3/frame (21).png", L"resources/sprites/people/boy3/frame (22).png", L"resources/sprites/people/boy3/frame (23).png", L"resources/sprites/people/boy3/frame (24).png"}},
			{"Left", {L"resources/sprites/people/boy3/frame (25).png", L"resources/sprites/people/boy3/frame (26).png", L"resources/sprites/people/boy3/frame (27).png", L"resources/sprites/people/boy3/frame (28).png"}},
			{"Sest", {L"resources/sprites/people/boy3/frame (29).png", L"resources/sprites/people/boy3/frame (30).png", L"resources/sprites/people/boy3/frame (31).png", L"resources/sprites/people/boy3/frame (32).png"}},
		}
	},
	{
		HumanType_Girl1,
		{
			{"Foward", {L"resources/sprites/people/girl1/frame (1).png", L"resources/sprites/people/girl1/frame (2).png", L"resources/sprites/people/girl1/frame (3).png", L"resources/sprites/people/girl1/frame (4).png"}},
			{"Seast", {L"resources/sprites/people/girl1/frame (5).png", L"resources/sprites/people/girl1/frame (6).png", L"resources/sprites/people/girl1/frame (7).png", L"resources/sprites/people/girl1/frame (8).png"}},
			{"Right", {L"resources/sprites/people/girl1/frame (9).png", L"resources/sprites/people/girl1/frame (10).png", L"resources/sprites/people/girl1/frame (11).png", L"resources/sprites/people/girl1/frame (12).png"}},
			{"Neast", {L"resources/sprites/people/girl1/frame (13).png", L"resources/sprites/people/girl1/frame (14).png", L"resources/sprites/people/girl1/frame (15).png", L"resources/sprites/people/girl1/frame (16).png"}},
			{"Backward", {L"resources/sprites/people/girl1/frame (17).png", L"resources/sprites/people/girl1/frame (18).png", L"resources/sprites/people/girl1/frame (19).png", L"resources/sprites/people/girl1/frame (20).png"}},
			{"Nest", {L"resources/sprites/people/girl1/frame (21).png", L"resources/sprites/people/girl1/frame (22).png", L"resources/sprites/people/girl1/frame (23).png", L"resources/sprites/people/girl1/frame (24).png"}},
			{"Left", {L"resources/sprites/people/girl1/frame (25).png", L"resources/sprites/people/girl1/frame (26).png", L"resources/sprites/people/girl1/frame (27).png", L"resources/sprites/people/girl1/frame (28).png"}},
			{"Sest", {L"resources/sprites/people/girl1/frame (29).png", L"resources/sprites/people/girl1/frame (30).png", L"resources/sprites/people/girl1/frame (31).png", L"resources/sprites/people/girl1/frame (32).png"}},
		}
	},
	{
		HumanType_Girl2,
		{
			{"Foward", {L"resources/sprites/people/girl2/frame (1).png", L"resources/sprites/people/girl2/frame (2).png", L"resources/sprites/people/girl2/frame (3).png", L"resources/sprites/people/girl2/frame (4).png"}},
			{"Seast", {L"resources/sprites/people/girl2/frame (5).png", L"resources/sprites/people/girl2/frame (6).png", L"resources/sprites/people/girl2/frame (7).png", L"resources/sprites/people/girl2/frame (8).png"}},
			{"Right", {L"resources/sprites/people/girl2/frame (9).png", L"resources/sprites/people/girl2/frame (10).png", L"resources/sprites/people/girl2/frame (11).png", L"resources/sprites/people/girl2/frame (12).png"}},
			{"Neast", {L"resources/sprites/people/girl2/frame (13).png", L"resources/sprites/people/girl2/frame (14).png", L"resources/sprites/people/girl2/frame (15).png", L"resources/sprites/people/girl2/frame (16).png"}},
			{"Backward", {L"resources/sprites/people/girl2/frame (17).png", L"resources/sprites/people/girl2/frame (18).png", L"resources/sprites/people/girl2/frame (19).png", L"resources/sprites/people/girl2/frame (20).png"}},
			{"Nest", {L"resources/sprites/people/girl2/frame (21).png", L"resources/sprites/people/girl2/frame (22).png", L"resources/sprites/people/girl2/frame (23).png", L"resources/sprites/people/girl2/frame (24).png"}},
			{"Left", {L"resources/sprites/people/girl2/frame (25).png", L"resources/sprites/people/girl2/frame (26).png", L"resources/sprites/people/girl2/frame (27).png", L"resources/sprites/people/girl2/frame (28).png"}},
			{"Sest", {L"resources/sprites/people/girl2/frame (29).png", L"resources/sprites/people/girl2/frame (30).png", L"resources/sprites/people/girl2/frame (31).png", L"resources/sprites/people/girl2/frame (32).png"}},
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
	void set_human_type(HumanTypes type) { nAttributes["type"] = type; }
};