#pragma once
#include <d3d9.h>

struct Sprite {
	// Origin
	int x = 0, 
		y = 0;
	
	// Rect
	int left = 0, top = 0,
		right = 0, bottom = 0;
	
	LPDIRECT3DTEXTURE9 texture = nullptr;
};