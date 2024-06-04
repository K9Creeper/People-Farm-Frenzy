#pragma once
#include <Windows.h>

namespace SoundSystem {
	extern bool Play(LPCWSTR src, DWORD args);
	extern bool StopAllSounds();
};