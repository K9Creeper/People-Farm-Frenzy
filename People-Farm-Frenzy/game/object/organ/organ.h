#pragma once
#include <cstring>
#include "../object.h"

enum OrganTypes : uint16_t {
	OrganType_Brain = 0,
	OrganType_Heart,
	OrganType_Lung,
	OrganType_Kidney,
	OrganType_Eyeball,
	OrganType_Intestine,
	OrganType_Stomach,
	OrganType_Skin,
	OrganType_Skull
};

static std::unordered_map <OrganTypes, double>OrganChances{
	// ORGAN				CHANCE
	{OrganType_Brain,		.5 / 100.f},
	{OrganType_Heart ,		2 / 100.f},
	{OrganType_Lung ,		3 / 100.f},
	{OrganType_Kidney ,		4 / 100.f},
	{OrganType_Eyeball ,	5 / 100.f},
	{OrganType_Intestine ,	10 / 100.f },
	{OrganType_Stomach ,	15 / 100.f},
	{OrganType_Skin ,		30 / 100.f},
	{OrganType_Skull ,		30.5 / 100.f },
};

static std::unordered_map <OrganTypes, double>OrganValues{
	// ORGAN				PRICE
	{OrganType_Brain,		200.f},
	{OrganType_Heart ,		50.f},
	{OrganType_Lung ,		30.f},
	{OrganType_Kidney ,		25.f},
	{OrganType_Eyeball ,	20.f},
	{OrganType_Intestine ,	15.f },
	{OrganType_Stomach ,	10.f},
	{OrganType_Skin ,		6.f},
	{OrganType_Skull ,		5.f },
};

static std::unordered_map <OrganTypes, std::string>OrganNames{
	// ORGAN				String
	{OrganType_Brain,		"Brain"},
	{OrganType_Heart ,		"Heart"},
	{OrganType_Lung ,		"Lung"},
	{OrganType_Kidney ,		"Kidney"},
	{OrganType_Eyeball ,	"Eyeball"},
	{OrganType_Intestine ,	"Intestine"},
	{OrganType_Stomach ,	"Stomach"},
	{OrganType_Skin ,		"Skin"},
	{OrganType_Skull ,		"Skull"},
};

static std::unordered_map<OrganTypes, LPCWSTR>OrganTextures{
	// ORGAN				SRC
	{OrganType_Brain,		L"resources/sprites/organs/brain.png"},
	{OrganType_Heart ,		L"resources/sprites/organs/heart.png"},
	{OrganType_Lung ,		L"resources/sprites/organs/lung.png"},
	{OrganType_Kidney ,		L"resources/sprites/organs/kidney.png"},
	{OrganType_Eyeball ,	L"resources/sprites/organs/eyeball.png"},
	{OrganType_Intestine ,	L"resources/sprites/organs/intestine.png"},
	{OrganType_Stomach ,	L"resources/sprites/organs/stomach.png"},
	{OrganType_Skin ,		L"resources/sprites/organs/skin.png"},
	{OrganType_Skull ,		L"resources/sprites/organs/skull.png"},
};

class Organ : public GameObject {
public:
	std::string get_organ_name() { return sAttributes["name"]; }
	OrganTypes get_organ_type() { return (OrganTypes)nAttributes["type"]; }
	float get_value() { return OrganValues[get_organ_type()]; }
};