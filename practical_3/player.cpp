
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
	
	// player movement with momentum
	
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
	
	
	
	// restrict player movement to maze path
	
	sf::Vector2ul newPos;
	newPos.x = _position.x + (moveLeft * dt) + (moveRight * dt);
	newPos.y = _position.y + (moveUp * dt) + (moveDown * dt);
	
	// get tile centre screen coordinates from player screen coordinates
	
	float tileX = (floor(newPos.x / ls::getTileSize()) * ls::getTileSize()) + ls::getTileSize() / 2;
	float tileY = (floor(newPos.y / ls::getTileSize()) * ls::getTileSize()) + ls::getTileSize() / 2;
	
	float max;
	
	if (moveUp + moveDown < 0) { // going up - check tiles above
		
		// indexes for tile directly above
		size_t destX = floor(tileX / ls::getTileSize());
		size_t destY = floor(tileY / ls::getTileSize()) - 1;
		max = 0;
		
		while (max == 0 && destY >= 0) {
			ls::TILE dest = ls::getTile({destX, destY});
			
			if (dest == ls::WALL) {
				max = (destY + 1) * ls::getTileSize();
				if (newPos.y < max + 25) {
					newPos.y = max + 25;
				}
			}
			destY--;
		}
		
		// check upper right tile
		if (newPos.x > tileX) {
			
			// get bottom right corner of this tile
			int verticeX = tileX + ls::getTileSize() / 2;
			int verticeY = tileY - ls::getTileSize() / 2;
			
			// calculate maximum available distance from current position
			double sideP = verticeX - _position.x;
			if (sideP < 25){
				double sideV = sqrt(pow(25,2) - pow(sideP,2));
				double maxDistance = _position.y - verticeY - sideV;
				
				// update destination if necessary
				if (newPos.y < _position.y - maxDistance) {
					newPos.y = _position.y - maxDistance;
				}
			}
		}		
		 
		// check upper left tile
		if (newPos.x < tileX) {
		
			// get top left corner of this tile
			int verticeX = tileX - ls::getTileSize() / 2;
			int verticeY = tileY - ls::getTileSize() / 2;
		
			// calculate maximum available distance from current position
			double sideP = verticeX - _position.x;
			if (sideP < 25) {
				double sideV = sqrt(pow(25,2) - pow(sideP,2));
				double maxDistance = _position.y - verticeY - sideV;

				// update destination if necessary
				if (newPos.y < _position.y - maxDistance) {
					newPos.y = _position.y - maxDistance;
				}
			}
		} 
		
	}
	
	if (moveUp + moveDown > 0) { // going down - check tiles below
		
		// indexes for tile directly below
		size_t destX = floor(tileX / ls::getTileSize());
		size_t destY = floor(tileY / ls::getTileSize()) + 1;
		max = 0;
		
		while (max == 0 && destY <= ls::getHeight()) {
			ls::TILE dest = ls::getTile({destX, destY});
			
			if (dest == ls::WALL) {
				max = (destY - 0) * ls::getTileSize();
				if (newPos.y > max - 25) {
					newPos.y = max - 25;
				}
			}
			destY++;
		}
		
		
		// check lower right tile
		if (newPos.x > tileX) {
			
			// get bottom right corner of this tile
			int verticeX = tileX + ls::getTileSize() / 2;
			int verticeY = tileY + ls::getTileSize() / 2;
			
			// calculate maximum available distance from current position
			double sideP = verticeX - _position.x;
			if (sideP < 25){
				double sideV = sqrt(pow(25,2) - pow(sideP,2));
				double maxDistance = verticeY - _position.y - sideV;
				
				// update destination if necessary
				if (newPos.y > _position.y + maxDistance) {
					newPos.y = _position.y + maxDistance;
				}
			}
		}		
		 
		// check lower left tile
		if (newPos.x < tileX) {
		
			// get bottom left corner of this tile
			int verticeX = tileX - ls::getTileSize() / 2;
			int verticeY = tileY + ls::getTileSize() / 2;
		
			// calculate maximum available distance from current position
			double sideP = _position.x - verticeX;
			if (sideP < 25) {
				double sideV = sqrt(pow(25,2) - pow(sideP,2));
				double maxDistance = verticeY - _position.y - sideV;

				// update destination if necessary
				if (newPos.y > _position.y + maxDistance) {
					newPos.y = _position.y + maxDistance;
				}
			}
		} 
		
	}
	
	if (moveRight + moveLeft > 0) { // going right - check tiles to right
		
		// indexes for tile directly to right
		size_t destX = ceil(tileX / ls::getTileSize());
		size_t destY = floor(tileY / ls::getTileSize());
		max = 0;
		
		while (max == 0 && destX <= ls::getWidth()) {
			ls::TILE dest = ls::getTile({destX, destY});
			if (dest == ls::WALL) {
				max = destX * ls::getTileSize();
				if (newPos.x > max - 25) {
					newPos.x = max - 25;
				}
			}
			destX++;
		}
		
		// check upper right tile
		if (newPos.y < tileY) {
			
			// get top right corner of this tile
			int verticeX = tileX + ls::getTileSize() / 2;
			int verticeY = tileY - ls::getTileSize() / 2;
			
			// calculate maximum available distance from current position
			double sideP = _position.y - verticeY;
			
			if (sideP < 25) {
				double sideV = sqrt(pow(25,2) - pow(sideP,2));
				double maxDistance = verticeX - _position.x - sideV;

				// update destination if necessary
				if (newPos.x > _position.x + maxDistance) {
					newPos.x = _position.x + maxDistance;
				}
			}
		}		
		
		// check lower right tile
		if (newPos.y > tileY) {
		
			// get bottom right corner of this tile
			int verticeX = tileX + ls::getTileSize() / 2;
			int verticeY = tileY + ls::getTileSize() / 2;
		
			// calculate maximum available distance from current position
			double sideP = verticeY - _position.y;
			
			if (sideP < 25) {
				double sideV = sqrt(pow(25,2) - pow(sideP,2));
				double maxDistance = verticeX - _position.x - sideV;

				// update destination if necessary
				if (newPos.x > _position.x + maxDistance) {
					newPos.x = _position.x + maxDistance;
				}
			}
		}		
		
	}
	
	if (moveRight + moveLeft < 0) { // going left - check tiles to left
		
		// indexes for tiles directly to the left
		size_t destX = floor(tileX / ls::getTileSize()) - 1;
		size_t destY = floor(tileY / ls::getTileSize());
		max = 0;
		
		while (max == 0 && destX >= 0) {
			ls::TILE dest = ls::getTile({destX, destY});
			if (dest == ls::WALL) {
				max = (destX + 1) * ls::getTileSize();
				if (newPos.x < max + 25) {
					newPos.x = max + 25;
				}
			}
			destX--;
		}
		
		// check upper left tile
		if (newPos.y < tileY) {
			
			// get top left corner of this tile
			int verticeX = tileX - ls::getTileSize() / 2;
			int verticeY = tileY - ls::getTileSize() / 2;
			
			// calculate maximum available distance from current position
			double sideP = _position.y - verticeY;
			
			if (sideP < 25) {
				double sideV = sqrt(pow(25,2) - pow(sideP,2));
				double maxDistance = _position.x - verticeX - sideV;

				// update destination if necessary
				if (newPos.x < _position.x - maxDistance) {
					newPos.x = _position.x - maxDistance;
				}
			}		
		}
		
		// check lower left tile
		if (newPos.y > tileY) {
		
			// get bottom left corner of this tile
			int verticeX = tileX - ls::getTileSize() / 2;
			int verticeY = tileY + ls::getTileSize() / 2;
		
			// calculate maximum available distance from current position
			double sideP = verticeY - _position.y;
			
			if (sideP < 25) {
				double sideV = sqrt(pow(25,2) - pow(sideP,2));
				double maxDistance = _position.x - verticeX - sideV;

				// update destination if necessary
				if (newPos.x < _position.x - maxDistance) {
					newPos.x = _position.x - maxDistance;
				}
			}		
		}
	}
		
	_position.x = newPos.x;
	_position.y = (newPos.y);
		
	Entity::update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.f,25.f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}