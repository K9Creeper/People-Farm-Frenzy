#pragma once
#include <cstring>
#include "../object.h"

enum LivingSpaceTypes : uint16_t {
	LivingSpaceType_None = 0,
	LivingSpaceType_Shack,
	LivingSpaceType_House,
	LivingSpaceType_Duplex,
	LivingSpaceType_Apartment,
	LivingSpaceType_Warehouse,
	LivingSpaceType_Skyscraper
};

static std::unordered_map <LivingSpaceTypes, std::string>LivingSpaceNames{
	// LivingSpaceTypes				String
	{LivingSpaceType_None,			"None"},
	{LivingSpaceType_Shack,			"Shack"},
	{LivingSpaceType_House ,		"House"},
	{LivingSpaceType_Duplex ,		"Duplex"},
	{LivingSpaceType_Apartment ,	"Apartment"},
	{LivingSpaceType_Warehouse ,	"Warehouse"},
	{LivingSpaceType_Skyscraper ,	"Skyscraper"},
};

static std::unordered_map <LivingSpaceTypes, int>LivingSpaceCapacity{
	// LivingSpaceTypes				Capacity
	{LivingSpaceType_None,			0},	
	{LivingSpaceType_Shack,			25},
	{LivingSpaceType_House ,		50},
	{LivingSpaceType_Duplex ,		100},
	{LivingSpaceType_Apartment ,	500},
	{LivingSpaceType_Warehouse ,	1000},
	{LivingSpaceType_Skyscraper ,	5000},
};

/*
Todo:
	1. Put in textures for unordered_map of textures for each LivingSpace
*/

static std::unordered_map<LivingSpaceTypes, LPCWSTR>LivingSpaceTextures{
	// LivingSpaceTypes				SRC
	{LivingSpaceType_None,			L""},
	{LivingSpaceType_Shack,			L"resources/sprites/livingspace/shack.png"},
	{LivingSpaceType_House ,		L"resources/sprites/livingspace/house.png"},
	{LivingSpaceType_Duplex ,		L"resources/sprites/livingspace/duplex.png"},
	{LivingSpaceType_Apartment ,	L"resources/sprites/livingspace/apartment.png"},

	// Max is useless LEEETS BEEE HONEST
	// jk.. gj max


	// THIS DOES NOT HAVE ANYTHING
	{LivingSpaceType_Warehouse ,	L"resources/sprites/livingspace/apartment.png"},
	{LivingSpaceType_Skyscraper ,	L"resources/sprites/livingspace/apartment.png"},
};

struct LivingSpaceSlotInfo {
	int x, width, height;
};

static std::unordered_map<int, LivingSpaceSlotInfo>LivingSpaceSlotInfos{
	// LivingSpaceTypes				SRC
	{1,			LivingSpaceSlotInfo{95, 259, 53}},
	{2,			LivingSpaceSlotInfo{510, 259, 53}},
	{3 ,		LivingSpaceSlotInfo{925, 259, 53}},
};

class LivingSpace : public GameObject {
public:
	std::string get_space_name() { return LivingSpaceNames[get_space_type()]; }
	LivingSpaceTypes get_space_type() { return (LivingSpaceTypes)nAttributes["type"]; }
	int get_max_capacity() { return LivingSpaceCapacity[get_space_type()]; }
	int get_current_capacity() { return nAttributes["current_capacity"]; }
	void set_current_capacity(const int& cap) { nAttributes["current_capacity"] = cap; }
	int get_slot() { return nAttributes["slot"]; }
};