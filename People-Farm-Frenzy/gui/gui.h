#pragma once
#include <Windows.h>

#include <functional>
#include <vector>

#include "floodgui/flood_gui.h"
#include "floodgui/flood_gui_win.h"
#include "floodgui/flood_gui_draw.h"

#include "d3dx9/Include/d3dx9.h"
#pragma comment(lib, "gui/d3dx9/Lib/x64/d3dx9")

typedef void(*render_handle_fn)(void);

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

	std::vector<render_handle_fn>renderHandles;

	std::unordered_map<LPCWSTR, LPDIRECT3DTEXTURE9>loadedTextures;
public:
	void AddRenderHandle(render_handle_fn handle);

	bool CreateDeviceD3D();
	void CleanupDeviceD3D();

	void FloodSetUp();

	void RunFlood();

	LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR src);
};

namespace GUI {
	inline Window* window = nullptr;
	inline Gui* gui = nullptr;

}