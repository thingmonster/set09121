
#include <iostream>
#include "cmp_enemy_movement.h"

using namespace sf;
using namespace std;

void EnemyMovementComponent::update(double dt) {
	
	
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
		
	float x = _parent->getPosition().x;
	float y = _parent->getPosition().y;
	
	x += moveX * dt;
	y += moveY * dt;
	
	_parent->setPosition({x, y});
	
	
}

EnemyMovementComponent::EnemyMovementComponent(Entity *p) : ActorMovementComponent(p) {}
