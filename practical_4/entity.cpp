
#include <iostream>
#include "entity.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

const Vector2f Entity::getPosition() {
	return _position;
}

void Entity::setPosition(const Vector2f &pos) {
	_position = pos;
}

float Entity::getRadius() {
	return _radius;
}

void Entity::move(const Vector2f &pos) {
	_position += pos;
}

bool Entity::update(const double dt) {
	_shape->setPosition(_position);
	return true;
}

Entity::Entity(unique_ptr<Shape> s) : _radius(25.f), _shape(std::move(s)) {
}




void EntityManager::update(double dt) {
	
	for (auto &e : list) {
		e->update(dt);
	}
}
	
void EntityManager::render() {
	
	for (auto &e : list) {
		e->render();
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	