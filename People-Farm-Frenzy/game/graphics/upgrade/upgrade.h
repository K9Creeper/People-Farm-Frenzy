#pragma once
#include <cstring>
#include <functional>

//								 void* <- this is going to be a ptr to the structure itself.
typedef void(*upgrade_handle_fn)(void*);

template<typename T>
struct Upgrade {
	T Value;
	
	double nextLevelCost = 0.f;
	int level = 0;
	int levelMax = 0;

	upgrade_handle_fn upgradeHandle;
};

struct UpgradeWindow {
	bool show = false;
	std::string window_name{};
};

template<typename T>
void CreateUpGradeWindow(UpgradeWindow* window, std::vector<Upgrade<T>>& upgrades);