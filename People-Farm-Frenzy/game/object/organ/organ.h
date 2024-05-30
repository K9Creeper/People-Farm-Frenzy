#pragma once
#include <cstring>
#include "../object.h"

enum OrganTypes : uint16_t {
	OrganType_Brain = 0,
	OrganType_Heart,
	OrganType_Stomach,
	OrganType_Lung,
	OrganType_Kidney,
	OrganType_Intestine,
	OrganType_Eyeball,
	OrganType_Bone,
	OrganType_Skin
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
	{OrganType_Bone ,		30.5 / 100.f },
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
	{OrganType_Bone ,		5.f },
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
	{OrganType_Bone ,		"Bone"},
};

class Organ : public GameObject {
public:
	std::string get_organ_name() { return sAttributes["name"]; }
	OrganTypes get_organ_type() { return (OrganTypes)nAttributes["type"]; }
	float get_value() { return nAttributes["value"]; }
};