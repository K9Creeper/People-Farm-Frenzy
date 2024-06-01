#pragma once
#include "../object.h"
#include "../../graphics/sprite/sprite.h"

enum VFXType : uint16_t {
	VFXType_None = 0,
	VFXType_BloodCloud
};

static std::unordered_map<VFXType, std::vector<LPCWSTR>>VFXTextures{
	// LivingSpaceTypes				SRC
	{VFXType_None,			{L""}},
	{VFXType_BloodCloud,			{L"resources/sprites/BloodCloud/frame_0_delay-0.08s.png", L"resources/sprites/BloodCloud/frame_1_delay-0.08s.png", L"resources/sprites/BloodCloud/frame_2_delay-0.08s.png", L"resources/sprites/BloodCloud/frame_3_delay-0.08s.png",
									L"resources/sprites/BloodCloud/frame_4_delay-0.08s.png", L"resources/sprites/BloodCloud/frame_5_delay-0.08s.png", L"resources/sprites/BloodCloud/frame_6_delay-0.08s.png", L"resources/sprites/BloodCloud/frame_7_delay-0.08s.png",
											L"resources/sprites/BloodCloud/frame_8_delay-0.08s.png" }}
};

class VFX : public GameObject {
public:
	VFXType get_vfx_type() { return (VFXType)nAttributes["type"]; }
};