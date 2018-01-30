
#include <iostream>
#include "game.h"
#include "ship.h"
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
		
void Bullet::Fire(sf::Vector2f &pos, bool mode) {
	
	this->setPosition(pos);
	this->visible = true;
	
	if (mode) {
		this->_mode = true;
	} else {
		this->_mode = false;
	}
	
	bulletPointer++;
};

void Bullet::Update(const float &dt) {
	if (visible) {
		move(0, dt * 200.0f * (-1.9f));
		const FloatRect boundingBox = getGlobalBounds();
		
		for (auto s : ships) {
			
			if (!_mode && s != ships[0]) {
				if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox)) {
					visible = false;
					s->explode();
				}
			} else if (_mode && s == ships[0]) {
				if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox)) {
					visible = false;
					s->explode();
				}
			}
		}
	}
};

bool Bullet::getVisibility() {
	return visible;
};

unsigned char Bullet::getBulletPointer() {
	return bulletPointer;
};



















