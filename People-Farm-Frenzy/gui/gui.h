#pragma once
#include <Windows.h>

#include "floodgui/flood_gui.h"
#include "floodgui/flood_gui_draw.h"
#include "floodgui/flood_gui_math.h"

class Window;
class Gui {
public:
	Gui(Window* window);
	~Gui();
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	D3DPRESENT_PARAMETERS d3dpp;

	Window* window;
public:

};