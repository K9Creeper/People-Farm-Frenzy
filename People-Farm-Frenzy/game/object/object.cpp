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


constexpr void ModRect(const int& x, const int& y, int& l, int& t, int& r, int& b)
{
	const int& width = r - l;
	const int& height = b - t;

	l = x - width / 2;
	t = y - height / 2;

	b = x + width / 2;
	r = y + height / 2;
}

void GameObject::SetSize(const int& width, const int& height) {
	sprite.left -= width / 2 + sprite.x;
	sprite.top -= height / 2 + sprite.x;
	sprite.right += width / 2 + sprite.x;
	sprite.bottom += height / 2 + sprite.x;
}

void GameObject::SetPosition(const int& x, const int& y) {
	sprite.x = x;
	sprite.y = y;

	ModRect(sprite.x, sprite.y, sprite.left, sprite.top, sprite.right, sprite.bottom);
}