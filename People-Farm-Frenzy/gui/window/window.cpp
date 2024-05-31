#include "window.h"

extern LRESULT CALLBACK FloodGuiWindowWinProcHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (FloodGuiWindowWinProcHandler(hwnd, message, wParam, lParam))
		return TRUE;

	switch (message)
	{
	case WM_PAINT:
	{

		break;
	}
	case WM_SIZE:
	{
		if (!FloodGui::Context.Initalized)
			break;
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
		break;
	}
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

void Window::Initalize(Gui* gui) {
	this->gui = gui;
	{
		wc = { sizeof(wc), CS_CLASSDC, MainWindowProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"People-Farm-Frenzy0", nullptr };
		RegisterClassExW(&wc);
		hwnd = ::CreateWindowW(wc.lpszClassName, L"People-Farm-Frenzy", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, width, height, nullptr, nullptr, wc.hInstance, nullptr);

		// Initialize Direct3D
		if (!gui->CreateDeviceD3D())
		{
			gui->CleanupDeviceD3D();
			UnregisterClassW(wc.lpszClassName, wc.hInstance);
			return;
		}

		// Show the window
		ShowWindow(hwnd, SW_SHOWDEFAULT);
		UpdateWindow(hwnd);
	}

	gui->FloodSetUp();

	
}

Window::~Window() {
	FloodGuiD3D9Shutdown();
	FloodGuiWinShutdown();

	DestroyWindow(hwnd);
	UnregisterClassW(wc.lpszClassName, wc.hInstance);
}