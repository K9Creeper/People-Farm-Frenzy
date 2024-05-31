#include "object.h"

GameObjectType GameObject::GetType()const {
	return type;
}

void GameObject::SetType(GameObjectType type) {
	this->type = type;
}


Sprite* GameObject::GetSprite() {
	return &sprite;
}

void GameObject::SetSize(const int& width, const int& height) {
	const int& halfX = width / 2;
	const int& halfY = height / 2;
	sprite.left = sprite.x - halfX;
	sprite.top = sprite.y-halfY;
	sprite.right = halfX + sprite.x;
	sprite.bottom = halfY + sprite.y;
}

void GameObject::SetPosition(const int& x, const int& y) {
	const int& width = sprite.right - sprite.left;
	const int& height = sprite.bottom - sprite.top;

	sprite.x = x;
	sprite.y = y;

	SetSize(width, height);
}