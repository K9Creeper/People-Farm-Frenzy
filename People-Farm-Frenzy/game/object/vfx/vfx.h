#pragma once
#include "../object.h"
#include "../../graphics/sprite/sprite.h"

enum VFXType : uint16_t {
	VFXType_None = 0,
	VFXType_Fireball
};

static std::unordered_map<VFXType, std::vector<LPCWSTR>>VFXTextures{
	// LivingSpaceTypes				SRC
	{VFXType_None,			{L""}},
	{VFXType_Fireball,			{L"resources/sprites/fireball/frame_00_delay-0.08s.png", L"resources/sprites/fireball/frame_01_delay-0.08s.png", L"resources/sprites/fireball/frame_02_delay-0.08s.png", L"resources/sprites/fireball/frame_03_delay-0.08s.png",
									L"resources/sprites/fireball/frame_04_delay-0.08s.png", L"resources/sprites/fireball/frame_05_delay-0.08s.png", L"resources/sprites/fireball/frame_06_delay-0.08s.png", L"resources/sprites/fireball/frame_07_delay-0.08s.png",
											L"resources/sprites/fireball/frame_08_delay-0.08s.png", L"resources/sprites/fireball/frame_09_delay-0.08s.png" }}
};

class VFX : public GameObject {
public:
	VFXType get_vfx_type() { return (VFXType)nAttributes["type"]; }
};