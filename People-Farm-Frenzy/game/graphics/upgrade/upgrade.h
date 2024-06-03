#pragma once
#include <cstring>
#include <functional>

template<typename T>
struct Upgrade {
	T Value;
	int level = 0;
	int levelMax = 0;
};

struct UpgradeWindow {
	bool show = false;
	std::string window_name{};
};

template<typename T>
void CreateUpGradeWindow(UpgradeWindow* window, std::vector<Upgrade<T>>& upgrades);