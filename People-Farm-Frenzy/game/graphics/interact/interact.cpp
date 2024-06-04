#include "interact.h"
#include "../../../gui/gui.h"

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