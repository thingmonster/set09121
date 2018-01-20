
#include <iostream>
#include "game.h"
#include "ship.h"

using namespace sf;
using namespace std;

bool Invader::direction = false;
float Invader::speed = 100;

const Keyboard::Key controls[] = {
    Keyboard::Left,
    Keyboard::Right,
    Keyboard::Up
};

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
		direction = !direction;
		for (int i = 1; i < ships.size(); i++) {
			ships[i]->move(0, 24);
		}
	}

}

Player::Player() : Ship(IntRect (160,32,32,32)) {
	setPosition({gameHeight * .5f, gameHeight - 32.f});
	setOrigin(16,16);
}

void Player::Update(const float &dt) {
	
	Ship::Update(dt);
	
	int direction = 0;
	
    if ((Keyboard::isKeyPressed(controls[0])) && (getPosition().x > 20)) {
		direction--;
    }
	
    if ((Keyboard::isKeyPressed(controls[1])) && (getPosition().x < gameWidth - 20)) {
		direction++;
    }
	
    move(direction * dt * 400, 0);


}




