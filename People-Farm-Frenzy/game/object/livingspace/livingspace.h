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
	{LivingSpaceType_Warehouse ,	2000},
	{LivingSpaceType_Skyscraper ,	10000},
};

/*
Todo:
	1. Create a unordered_map of textures for each LivingSpace
*/

class LivingSpace : public GameObject {
	std::string get_space_name() { return LivingSpaceNames[get_space_type()]; }
	LivingSpaceTypes get_space_type() { return (LivingSpaceTypes)nAttributes["type"]; }
	int get_max_capacity() { return LivingSpaceCapacity[get_space_type()]; }
	int get_current_capacity() { return nAttributes["current_capacity"]; }
};