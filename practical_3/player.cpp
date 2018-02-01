
#include <iostream>	
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
	
	int direction = 0;
	
	if ((Keyboard::isKeyPressed(controls[0])) && (getPosition().x > 20)) {
		_position.x--;
	}

	if ((Keyboard::isKeyPressed(controls[1])) && (getPosition().x < gameWidth - 20)) {
		_position.x++;
	}

	if ((Keyboard::isKeyPressed(controls[2])) && (getPosition().x > 20)) {
		_position.y--;
	}

	if ((Keyboard::isKeyPressed(controls[3])) && (getPosition().x < gameHeight - 20)) {
		_position.y++;
	}

	Entity::update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Red);
	_shape->setOrigin(Vector2f(25.f,25.f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}