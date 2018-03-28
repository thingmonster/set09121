#include <iostream>
#include "cmp_enemy_movement.h"

using namespace sf;
using namespace std;

//																		right  down   up    left
static const Vector2i directions[] = {{1,0},{0,1},{0,-1},{-1,0}};

void EnemyMovementComponent::update(double dt) {
	
	const auto mva = (float)(dt * _speed);
	const Vector2f pos = _parent->getPosition();
	const Vector2f newpos = pos + (Vector2f)_direction * mva;
	std::srand(std::time(nullptr));
	
	Vector2ul check;
	vector<int> validDirections;
	int rand;
	
	switch (_state) {
		case STARTING: {
			
			for (int i = 0; i < (sizeof(directions)/sizeof(*directions)); ++i) {
				
				check = LevelSystem::screenCoordsToIndexes(newpos);
				check.x += directions[i].x;
				check.y += directions[i].y;
				if (LevelSystem::getTile(check) != LevelSystem::WALL) {
					validDirections.push_back(i);
				}
			}
			
			rand = std::rand() % validDirections.size();
			_direction = directions[validDirections[rand]];
			_state = ROAMING;
			break;
		}
		case ROAMING: {
			roaming(mva);
			break;
		}
		case ROTATING: {
			rotating(mva);
			break;
		}
		case ROTATED: {
			rotated(mva);
			break;
		}
	}
	
	/*
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
		
	// float x = _parent->getPosition().x;
	// float y = _parent->getPosition().y;
	
	// x += moveX * dt;
	// y += moveY * dt;
	
	moveX *= dt;
	moveY *= dt;
	
	float floatX = (float)moveX;
	float floatY = (float)moveY;
	
	move({floatX, floatY});
	*/
	
}

void EnemyMovementComponent::roaming(float mva) {
		
	const Vector2f pos = _parent->getPosition();
	const Vector2f newpos = pos + (Vector2f)_direction * mva;
	Vector2ul check;
	Vector2f checkf;
	int tileSize = LevelSystem::getTileSize();
	
	

	checkf.x = newpos.x + (tileSize / 2 * _direction.x);
	checkf.y = newpos.y + (tileSize / 2 * _direction.y);
	
	if (
		(LevelSystem::getTileFromScreenCoords(checkf) == LevelSystem::WALL) ||
		(
			(LevelSystem::getTileFromScreenCoords(newpos) == LevelSystem::WAYPOINT) &&
			(
				((_direction.x == 1) && (fmod(newpos.x, tileSize) > 10)) || 
				((_direction.x == -1) && (fmod(newpos.x, tileSize) < 13)) || 
				((_direction.y == 1) && (fmod(newpos.y, tileSize) > 10)) || 
				((_direction.y == -1) && (fmod(newpos.y, tileSize) < 13))
			)
		)
	) {
	
		_state = ROTATING;
	} else {
		check = LevelSystem::screenCoordsToIndexes(pos);
		move((Vector2f)_direction * mva);
	}
		
}

void EnemyMovementComponent::rotating(float mva) {
	
	const Vector2f pos = _parent->getPosition();
	const Vector2f newpos = pos + (Vector2f)_direction * mva;
	const Vector2i baddir =  -1 * Vector2i(_direction);
	Vector2ul check;
	vector<int> validDirections;
	int rand;
	std::srand(std::time(nullptr));
	

	for (int i = 0; i < (sizeof(directions)/sizeof(*directions)); ++i) {
		
		check = LevelSystem::screenCoordsToIndexes(newpos);
		check.x += directions[i].x;
		check.y += directions[i].y;
		if (
			(LevelSystem::getTile(check) != LevelSystem::WALL) &&
			(directions[i] != baddir)
		) {
			validDirections.push_back(i);
		}	else {
		}
	}
	
	rand = std::rand() % validDirections.size();
	_direction = directions[validDirections[rand]];
	_state = ROTATED;
	rotated(mva);
}

void EnemyMovementComponent::rotated(float mva) {
	
	const Vector2f pos = _parent->getPosition();
	const Vector2f newpos = pos + (Vector2f)_direction * mva;
	
	if (LevelSystem::getTileFromScreenCoords(newpos) != LevelSystem::WAYPOINT) {
		_state = ROAMING;
	} 
	move((Vector2f)_direction * mva);
			
}

EnemyMovementComponent::EnemyMovementComponent(Entity *p) : ActorMovementComponent(p) {
	_state = STARTING;	
}














