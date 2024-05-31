#pragma once
#include "../object.h"
#include "../../graphics/sprite/sprite.h"

enum SFXType : uint16_t {
	SFXType_None = 0,
	SFXType_Fireball
};

static std::unordered_map<SFXType, std::vector<LPCWSTR>>SFXTextures{
	// LivingSpaceTypes				SRC
	{SFXType_None,			{L""}},
	{SFXType_Fireball,			{L"resources/sprites/fireball/frame_00_delay-0.08s.png", L"resources/sprites/fireball/frame_01_delay-0.08s.png", L"resources/sprites/fireball/frame_02_delay-0.08s.png", L"resources/sprites/fireball/frame_03_delay-0.08s.png",
									L"resources/sprites/fireball/frame_04_delay-0.08s.png", L"resources/sprites/fireball/frame_05_delay-0.08s.png", L"resources/sprites/fireball/frame_06_delay-0.08s.png", L"resources/sprites/fireball/frame_07_delay-0.08s.png",
											L"resources/sprites/fireball/frame_08_delay-0.08s.png", L"resources/sprites/fireball/frame_09_delay-0.08s.png" }}
};

class SFX : public GameObject {
public:
	SFXType get_sfx_type() { return (SFXType)nAttributes["type"]; }
};