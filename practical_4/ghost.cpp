
#include <iostream>	
#include "ghost.h"
#include "system_renderer.h"


using namespace sf;
using namespace std;

void Ghost::update(double dt) {
	
	// 3% chance the ghost will change direction
	// 97% chance it will continue on its current path
	
	int direction = rand() % 100;
	float moveX = 0.f;
	float moveY = 0.f;
	
	if ((direction == 0) || (direction > 3 && _direction == 0)) {
		moveY = _speed * -1;
		_direction = 0;
	} else if ((direction == 1) || (direction > 3 && _direction == 1)) {
		moveY = _speed;
		_direction = 1;
	} else if ((direction == 2) || (direction > 3 && _direction == 2)) {
		moveX = _speed * -1;
		_direction = 2;
	} else if ((direction == 3) || (direction > 3 && _direction == 3)) {
		moveX = _speed;
		_direction = 3;
	}
	
	// update ghost's position
	
	_position.x += moveX * dt;
	_position.y += moveY * dt;
	
	Entity::update(dt);
		
}

Ghost::Ghost() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Red);
	_shape->setOrigin(Vector2f(_radius, _radius));
	setPosition({400,300});
	_direction = 1;
}

void Ghost::render() {
	Renderer::queue(_shape.get());
		
}