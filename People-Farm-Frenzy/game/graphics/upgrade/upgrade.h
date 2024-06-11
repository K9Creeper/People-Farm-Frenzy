#pragma once
#include <cstring>
#include <functional>

//										void* <- this is going to be a ptr to the structure itself.
typedef void(*upgrade_handle_fn)(void*, void*);

template<typename T>
struct Upgrade {
	T Value;
	
	uint64_t nextLevelCost = 0;
	std::string upgradeName;

	int level = 0;
	int levelMax = 0;

	upgrade_handle_fn upgradeHandle;
};