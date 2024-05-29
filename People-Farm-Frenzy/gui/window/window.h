#pragma once
#include <Windows.h>
#include "../gui.h"

class Gui;
class Window {
public:
	Window(const int& width, const int& height) : width(width), height(height){}
	~Window();

private:
	Gui* gui;
	
	WNDCLASSEXW wc;

	int width, height;
public:
	HWND hwnd;

	void Initalize(Gui* gui);
};