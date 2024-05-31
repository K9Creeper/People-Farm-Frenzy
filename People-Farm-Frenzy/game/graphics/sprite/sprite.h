#pragma once
#include <d3d9.h>

#include "../animation/animation.h"

struct Sprite {
	// Origin
	int x = 0, 
		y = 0;
	
	// Rect
	int left = 0, top = 0,
		right = 0, bottom = 0;
	
	LPDIRECT3DTEXTURE9 texture = nullptr;
	LPDIRECT3DTEXTURE9 textureOriginal = nullptr;

	//	Plays Designated Animation
	std::unordered_map<std::string, Animation>Animations;

	bool inAnimation = false;
	std::string curAnimation{};
	int animationFrame = 0;
	std::chrono::milliseconds tLastAnimationFrame = std::chrono::milliseconds(0);

	void StartAnimation(const std::string& name) {
		curAnimation.clear();
		inAnimation = false;
		animationFrame = 0;
		tLastAnimationFrame = std::chrono::milliseconds(0);
		if (Animations.find(name) == Animations.end())
			return;

		inAnimation = true;
		curAnimation = name;

		textureOriginal = texture;
	}
	
	void UpdateAnimation() {
		if (!inAnimation)
			return;
		Animation& animation = Animations[curAnimation];
		std::chrono::milliseconds currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		if (animationFrame < animation.frameDelay.size() && (animationFrame == 0 || currentTime - animation.frameDelay[animationFrame - 1] >= tLastAnimationFrame))
		{
			texture = animation.textures[animationFrame];
			tLastAnimationFrame = currentTime;
			
			animationFrame++;
		}
		else if (animationFrame >= animation.frameDelay.size()) {
			
			StopAnimation();
		}
	}

	void StopAnimation() {
		inAnimation = false;
		curAnimation.clear();
		animationFrame = 0;
		tLastAnimationFrame = std::chrono::milliseconds(0);
		texture = textureOriginal;
	}
};