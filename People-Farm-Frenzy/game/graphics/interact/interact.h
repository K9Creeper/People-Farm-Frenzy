#pragma once
#include <Windows.h>
#include "../../../gui/floodgui/flood_gui_math.h"

namespace Graphics {
	extern bool DrawTextureButton(LPCWSTR src, const float& x, const float& y, const float& width, const float& height, FloodColor col, const float& texx, const float& texy, const float& texwidth, const float& texheight);
	extern void DrawUIElement(const char* text, const int& textSize, const int& textSpacing, const float& x, const float& y, const float& width, const float& height, FloodColor col, LPCWSTR src);
	extern bool DrawTextButton(const char* text, const float& x, const float& y, const float& width, const float& height, FloodColor col, const int& fontS, const int& spacing);
}