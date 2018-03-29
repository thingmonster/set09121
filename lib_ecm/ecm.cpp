
#include <iostream>
#include "ecm.h"

using namespace sf;
using namespace std;
	

		
	
	
	
	
	
const Vector2f Entity::getPosition() {
	return _position;
}

void Entity::setPosition(const Vector2f &pos) {
	_position = pos;
}

void Entity::setForDelete() {
	_fordeletion = true;
}

bool Entity::is_fordeletion() {
	return _fordeletion;
}

float Entity::getRadius() {
	return _radius;
}

void Entity::move(const Vector2f &pos) {
	_position += pos;
}

void Entity::update(const double dt) {
	// _shape->setPosition(_position);
}

Entity::Entity(Scene* s) : scene(s), _fordeletion(false) {}





	
	
	
	
	
	
	
	

void EntityManager::update(double dt) {
	
	for (int i = 0; i < list.size(); i++) {
		if (list[i]->is_fordeletion()) {
			list.erase(list.begin() + i);
			--i;
			continue;
		}
	}
	
	for (auto &e : list) {
		for (auto &c : e->_components) {
			c->update(dt);
		}
	}
}
	
void EntityManager::render() {
	for (auto &e : list) {
		for (auto &c : e->_components) {
			c->render();
		}
	}
}
	
	
	
	
	
	
	
	
	
Component::Component(Entity *p) {_parent = p;}
void Component::update(double dt) {}
void Component::render() {}
	
	
	