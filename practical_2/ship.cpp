
#include <iostream>
#include "game.h"
#include "ship.h"

using namespace sf;
using namespace std;

bool Invader::direction;
float Invader::speed;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
}

void Ship::Update(const float &dt) {}

Ship::~Ship() = default;


Invader::Invader() : Ship() {}
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
	direction = true;
}

void Invader::Update(const float &dt) {
	
	Ship::Update(dt);
	
	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);
	
	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
		cout << "test";
		if (direction) {
			direction = false;
		} else {
			direction = true;
		}
	}

	float newPos;
	if (direction) {
		newPos = 24;
	} else {
		newPos = -24;
	}
	
	for (int i = 0; i < ships.size(); i++) {
		ships[i]->move(newPos, 0);
	}
}


