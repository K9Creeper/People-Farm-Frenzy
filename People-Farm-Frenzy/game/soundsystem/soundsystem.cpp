#include "soundsystem.h"

bool SoundSystem::Play(LPCWSTR src, DWORD args) {
	return PlaySoundW(src, NULL, args);
}

bool SoundSystem::StopAllSounds() {
	return PlaySound(0, NULL, NULL);
}