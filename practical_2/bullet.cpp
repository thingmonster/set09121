
#include <iostream>
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

unsigned char Bullet::bulletPointer = 0;

Bullet::Bullet() {
	setTexture(spritesheet);
	_sprite = {64,32,32,32};
	setTextureRect(_sprite);
	setPosition({100,100});
	setOrigin(16,16);
	visible = false;
};
		
void Bullet::Fire(sf::Vector2f &pos) {
	this->setPosition(pos);
	this->visible = true;
	bulletPointer++;
};

void Bullet::Update(const float &dt) {
	if (visible) {
		move(0, dt * 200.0f * (-0.5f));
	}
};

bool Bullet::getVisibility() {
	return visible;
};

unsigned char Bullet::getBulletPointer() {
	return bulletPointer;
};



















