
#include <iostream>
#include <SFML/Graphics.hpp>
#include "cmp_actor_movement.h"
#include "levelsystem.h"


using namespace sf;

void ActorMovementComponent::update(double dt) {
	cout << "update" << endl;
}

ActorMovementComponent::ActorMovementComponent(Entity* p) : _speed(200.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
	auto pp = _parent->getPosition() + p;
	if (validMove(pp)) {
		move(pp.x, pp.y);
	}
}

void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}

float ActorMovementComponent::getSpeed() const {
	return _speed;
}

void ActorMovementComponent::setSpeed(float speed) {
	_speed = speed;
}