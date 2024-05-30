#pragma once
#include <cstring>
#include <functional>

struct UpgradeWindow {
	bool show = false;
	std::string window_name{};
	
	std::function<void()> render_handle = [](){};
};

template<typename T>
struct Upgrade {
	T Value;
	int level = 0;
	int levelMax = 0;
};