#pragma once
#include <Windows.h>

class Gui;
class Window {
public:
	Window(const int& width, const int& height) : width(width), height(height){}
	~Window();
private:
	Gui* gui;

	HWND hwnd;

	int width, height;


public:

};