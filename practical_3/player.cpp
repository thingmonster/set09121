
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

float Player::_momentum(float * timer) {
	
	float move = 0;

	move = _speed - pow( 210 - *timer * 20, 2);
	if (move < 0) {
		move = 0;
		*timer = 0;
	}

	return move;
	
}

void Player::update(double dt) {
	
	float moveLeft = 0;
	float moveRight = 0;
	float moveUp = 0;
	float moveDown = 0;
	
	static float lastMoveLeft = 0.0f;
	static float lastMoveRight = 0.0f;
	static float lastMoveUp = 0.0f;
	static float lastMoveDown = 0.0f;
	lastMoveLeft -= dt;
	lastMoveRight -= dt;
	lastMoveUp -= dt;
	lastMoveDown -= dt;
	
	if ((Keyboard::isKeyPressed(controls[0])) && (getPosition().x > 20)) {
		lastMoveLeft = 10.f;
		moveLeft = _speed * -1;
	} else {
		if (lastMoveLeft > 0) {
			moveLeft = _momentum(&lastMoveLeft) * -1;
		}
	}
	
	if ((Keyboard::isKeyPressed(controls[1])) && (getPosition().x < gameWidth - 20)) {
		lastMoveRight = 10.f;
		moveRight = _speed;
	} else {
		if (lastMoveRight > 0) {
			moveRight = _momentum(&lastMoveRight);
		}
	}
	
	if ((Keyboard::isKeyPressed(controls[2])) && (getPosition().y > 20)) {
		lastMoveUp = 10.f;
		moveUp = _speed * -1;
	} else {
		if (lastMoveUp > 0) {
			moveUp = _momentum(&lastMoveUp) * -1;
		}
	}
	
	if ((Keyboard::isKeyPressed(controls[3])) && (getPosition().y < gameHeight - 20)) {
		lastMoveDown = 10.f;
		moveDown = _speed;
	} else {
		if (lastMoveDown > 0) {
			moveDown = _momentum(&lastMoveDown);
		}
	}
	
	_position.x += (moveLeft * dt);
	_position.x += (moveRight * dt);
	_position.y += (moveUp * dt);
	_position.y += (moveDown * dt);
		
	Entity::update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.f,25.f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}