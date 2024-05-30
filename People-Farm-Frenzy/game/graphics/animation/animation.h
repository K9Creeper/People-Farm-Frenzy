#pragma once
#include <d3d9.h>
#include <vector>
#include <chrono>

class Animation{
public:
	Animation() : textures{}, frameDelay{}{	}
	Animation(std::vector<LPDIRECT3DTEXTURE9>textures, std::vector<std::chrono::milliseconds>frameDelay = {}) {
		this->textures = textures;
		this->frameDelay = frameDelay;

		if (this->frameDelay.size() == 0) {
			this->frameDelay.resize(this->textures.size());
			for (int i = 0; i < this->textures.size(); i++)
				this->frameDelay.push_back(std::chrono::milliseconds(17)); // Standard 60fps
		}
	}
	~Animation() { textures.clear(); frameDelay.clear(); }
	// Textures for each new animation frame
	std::vector<LPDIRECT3DTEXTURE9>textures;
	// Contains MS until next frame.
	std::vector<std::chrono::milliseconds>frameDelay;
};