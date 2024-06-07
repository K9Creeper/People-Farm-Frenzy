#include "interact.h"
#include "../../../gui/gui.h"

FloodVector2 CalculateTextSize(const char* text, const float& size, const float& spacing)
{
	return FloodVector2(static_cast<int>(strlen(text)) * (size + spacing), size * FONT_HEIGHT_MODIFIER);
}

bool Graphics::DrawTextureButton(LPCWSTR src, const float& x, const float& y, const float& width, const float& height, FloodColor col, const float& texx, const float& texy, const float& texwidth, const float& texheight) {
	const FloodVector2& min{ x, y };
	const FloodVector2& max{ x + width, y + height };
	
	const FloodVector2& texmin{ texx, texy };
	const FloodVector2& texmax{ texx + texwidth, texy + texheight };

	bool hit = false;
	if (FindPoint(min, max, FloodGui::Context.IO.mouse_pos)) {
		if (FloodGui::Context.IO.MouseInput[FloodGuiButton_LeftMouse]) {
			col.r() *= .75f;
			col.g() *= .75f;
			col.b() *= .75f;
			hit = true;
		}
		else {
			col.r() *= .85f;
			col.g() *= .85f;
			col.b() *= .85f;
		}
	}

	FloodGui::Context.GetForegroundDrawList()->AddRectFilled(min, max, col, nullptr);
	FloodGui::Context.GetForegroundDrawList()->AddRectFilled(texmin, texmax, FloodColor(1, 1, 1), GUI::gui->LoadTexture(src));
	return hit;
}

void Graphics::DrawUIElement(const char* text, const int& textSize, const int& textSpacing, const float& x, const float& y, const float& texwidth, const float& texheight, FloodColor col, LPCWSTR src) {
	FloodVector2 texVec( x, y );
	FloodVector2 topVec = texVec - (texwidth / 2.f);
	FloodVector2 botVec = texVec + (texheight / 2.f);

	const FloodVector2& textPos = FloodVector2(texVec) + FloodVector2(25, 0) + FloodVector2(texwidth / 2.f, (texheight / 4.f));

	FloodGui::Context.GetForegroundDrawList()->AddRectFilled(topVec, botVec, FloodColor(1, 1, 1), GUI::gui->LoadTexture(src));
	FloodGui::Context.GetForegroundDrawList()->AddText(text, textPos, col, textSize, textSpacing);
}
