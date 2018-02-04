
#include <iostream>	
#include "levelsystem.h"
#include "player.h"


using namespace sf;
using namespace std;

const Keyboard::Key controls[] = {
    Keyboard::Left,
    Keyboard::Right,
    Keyboard::Up,
    Keyboard::Down
};

void Player::update(double dt) {
	
	float moveX = 0;
	float moveY = 0;
	
	if ((Keyboard::isKeyPressed(controls[0])) && (getPosition().x > 20)) {
		moveX = -1;
	}

	if ((Keyboard::isKeyPressed(controls[1])) && (getPosition().x < gameWidth - 20)) {
		moveX = 1;
	}

	if ((Keyboard::isKeyPressed(controls[2])) && (getPosition().y > 20)) {
		moveY = -1;
	}

	if ((Keyboard::isKeyPressed(controls[3])) && (getPosition().y < gameHeight - 20)) {
		moveY = 1;
	}

	_position.x += (moveX * dt * _speed);
	_position.y += (moveY * dt * _speed);
		
	Entity::update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.f,25.f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}