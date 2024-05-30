#include "gui.h"

#include "window/window.h"

static const FloodColor clearColor(1.f, 1.f, 1.f, 1.f);

Gui::Gui(Window* window) {
	this->window = window;
}
Gui::~Gui() {
	for (auto& [src, texture] : loadedTextures) {
		texture->Release();
		texture = nullptr;
	}

	renderHandles.clear();
}

void Gui::AddRenderHandle(render_handle_fn handle) { renderHandles.push_back(handle); }

bool Gui::CreateDeviceD3D()
{
	if ((d3d = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr || !window)
		return false;

	// Create the D3DDevice
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
	if (d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window->hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3ddev) < 0)
		return false;

	return true;
}
void Gui::CleanupDeviceD3D()
{
	if (!window)
		return;
	if (d3ddev) { d3ddev->Release(); d3ddev = nullptr; }
	if (d3d) { d3d->Release(); d3d = nullptr; }
}

void Gui::FloodSetUp() {
	FloodGui::SetupColorStyle();
	FloodGuiWinInit(window->hwnd);
	FloodGuiD3D9Init(d3ddev);

	FloodGui::Context.DrawData = new FloodDrawData(&FloodGui::Context.Display);
}

void Gui::RunFlood() {
	static bool running = true;
	MSG msg;
	while (running) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { TranslateMessage(&msg); DispatchMessage(&msg); if (msg.message == WM_QUIT) { CleanupDeviceD3D(); running = false; } }
		if (!running)
			break;

		FloodGuiWinNewFrame();
		FloodGuiD3D9NewFrame();

		FloodGui::NewFrame();
		{
			// Render Area
			//
			for (int i = 0; i < renderHandles.size(); i++) { (renderHandles[i])(); }
		}
		FloodGui::EndFrame();

		d3ddev->SetRenderState(D3DRS_ZENABLE, FALSE);
		d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		d3ddev->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);


		d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clearColor.ToU32(), 1.0f, 0);

		if (d3ddev->BeginScene() >= 0)
		{
			FloodGui::Render();
			FloodGuiD3D9RenderDrawData(FloodGui::Context.DrawData);
			d3ddev->EndScene();
		}

		HRESULT result = d3ddev->Present(nullptr, nullptr, nullptr, nullptr);
	}
}

LPDIRECT3DTEXTURE9 Gui::LoadTexture(LPCWSTR src) {
	LPDIRECT3DTEXTURE9 texture;
	if (loadedTextures.find(src) != loadedTextures.end())
		return nullptr;
	if (D3D_OK != D3DXCreateTextureFromFile(d3ddev, src, &texture)) {
		texture->Release();
		return nullptr;
	}
	return (loadedTextures[src] = texture);
}