
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

double Player::_momentum(double * timer) {
	
	double move = 0;

	move = _speed - pow( 210 - *timer * 20, 2);
	if (move < 0) {
		move = 0;
		*timer = 0;
	}

	return move;
	
}

void Player::update(double dt) {
	
	// player movement with momentum
	
	double moveLeft = 0;
	double moveRight = 0;
	double moveUp = 0;
	double moveDown = 0;
	
	static double lastMoveLeft = 0.0f;
	static double lastMoveRight = 0.0f;
	static double lastMoveUp = 0.0f;
	static double lastMoveDown = 0.0f;
	
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
	
	// get screen coordinates for player's new position
	sf::Vector2f newPos;
	newPos.x = _position.x + (moveLeft * dt) + (moveRight * dt);
	newPos.y = _position.y + (moveUp * dt) + (moveDown * dt);
	
	// get tile centre screen coordinates from player screen coordinates	
	sf::Vector2f tile;
	tile.x = (floor(newPos.x / ls::getTileSize()) * ls::getTileSize()) + ls::getTileSize() / 2;
	tile.y = (floor(newPos.y / ls::getTileSize()) * ls::getTileSize()) + ls::getTileSize() / 2;
	
	float max;
	Vector2ul destination;
	
	
	if (moveUp + moveDown < 0) { // going up
		
		
		// check tiles directly above
		
		destination.x = floor(tile.x / ls::getTileSize());
		destination.y = floor(tile.y / ls::getTileSize()) - 1;
		
		max = 0;
		
		while (max == 0 && destination.y >= 0) {
			
			if (ls::getTile(destination) == ls::WALL) {
				max = (destination.y + 1) * ls::getTileSize();
				if (newPos.y < max + 25) {
					newPos.y = max + 25;
				}
			}
			destination.y--;
		}
		
		
		// check upper right tile
		
		if (newPos.x > tile.x) {
			
			// get bottom right corner of this tile
			Vector2f vertice = {
				tile.x + ls::getTileSize() / 2, 
				tile.y - ls::getTileSize() / 2
			};
			
			// calculate maximum available distance from current position
			float sideP = vertice.x - _position.x;
			if (sideP < 25){
				float sideV = sqrt(pow(25.f,2) - pow(sideP,2));
				float maxDistance = _position.y - vertice.y - sideV;
				
				// update destination if necessary
				if (newPos.y < _position.y - maxDistance) {
					newPos.y = _position.y - maxDistance;
				}
			}
		}		
		 
		
		// check upper left tile
		
		if (newPos.x < tile.x) {
		
			// get top left corner of this tile
			Vector2f vertice = {
				tile.x - ls::getTileSize() / 2, 
				tile.y - ls::getTileSize() / 2
			};
			
			// calculate maximum available distance from current position
			float sideP = vertice.x - _position.x;
			if (sideP < 25) {
				float sideV = sqrt(pow(25.f,2) - pow(sideP,2));
				float maxDistance = _position.y - vertice.y - sideV;

				// update destination if necessary
				if (newPos.y < _position.y - maxDistance) {
					newPos.y = _position.y - maxDistance;
				}
			}
		} 
		
	}
	 
	if (moveUp + moveDown > 0) { // going down
		
		
		// check tiles directly below
		
		destination.x = floor(tile.x / ls::getTileSize());
		destination.y = floor(tile.y / ls::getTileSize()) + 1;
		
		max = 0;
		
		while (max == 0 && destination.y <= ls::getHeight()) {
			
			if (ls::getTile(destination) == ls::WALL) {
				max = destination.y * ls::getTileSize();
				if (newPos.y > max - 25) {
					newPos.y = max - 25;
				}
			}
			destination.y++;
		}
		
		
		
		// check lower right tile
		
		if (newPos.x > tile.x) {
			
			// get bottom right corner of this tile
			Vector2f vertice = {
				tile.x - ls::getTileSize() / 2, 
				tile.y + ls::getTileSize() / 2
			};
			// calculate maximum available distance from current position
			float sideP = vertice.x - _position.x;
			if (sideP < 25){
				float sideV = sqrt(pow(25.f,2) - pow(sideP,2));
				float maxDistance = vertice.y - _position.y - sideV;
				
				// update destination if necessary
				if (newPos.y > _position.y + maxDistance) {
					newPos.y = _position.y + maxDistance;
				}
			}
		}		
		 
		
		// check lower left tile
		
		if (newPos.x < tile.x) {
		
			// get bottom left corner of this tile
			Vector2f vertice = {
				tile.x - ls::getTileSize() / 2, 
				tile.y + ls::getTileSize() / 2
			};
			// calculate maximum available distance from current position
			float sideP = _position.x - vertice.x;
			if (sideP < 25) {
				float sideV = sqrt(pow(25.f,2) - pow(sideP,2));
				float maxDistance = vertice.y - _position.y - sideV;

				// update destination if necessary
				if (newPos.y > _position.y + maxDistance) {
					newPos.y = _position.y + maxDistance;
				}
			}
		} 
		
	}
	
	if (moveRight + moveLeft > 0) { // going right
		
		
		// check tiles directly to right
		
		destination.x = floor(tile.x / ls::getTileSize()) + 1;
		destination.y = floor(tile.y / ls::getTileSize());
		
		max = 0;
		
		while (max == 0 && destination.x <= ls::getWidth()) {
			
			if (ls::getTile(destination) == ls::WALL) {
				max = destination.x * ls::getTileSize();
				if (newPos.x > max - 25) {
					newPos.x = max - 25;
				}
			}
			destination.x++;
		}
		
		
		// check upper right tile
		
		if (newPos.y < tile.y) {
			
			// get top right corner of this tile
			Vector2f vertice = {
				tile.x + ls::getTileSize() / 2, 
				tile.y - ls::getTileSize() / 2
			};
			// calculate maximum available distance from current position
			float sideP = _position.y - vertice.y;
			
			if (sideP < 25) {
				float sideV = sqrt(pow(25.f,2) - pow(sideP,2));
				float maxDistance = vertice.x - _position.x - sideV;

				// update destination if necessary
				if (newPos.x > _position.x + maxDistance) {
					newPos.x = _position.x + maxDistance;
				}
			}
		}		
		
		
		// check lower right tile
		
		if (newPos.y > tile.y) {
		
			// get bottom right corner of this tile
			Vector2f vertice = {
				tile.x + ls::getTileSize() / 2, 
				tile.y + ls::getTileSize() / 2
			};
			// calculate maximum available distance from current position
			float sideP = vertice.y - _position.y;
			
			if (sideP < 25) {
				float sideV = sqrt(pow(25.f,2) - pow(sideP,2));
				float maxDistance = vertice.x - _position.x - sideV;

				// update destination if necessary
				if (newPos.x > _position.x + maxDistance) {
					newPos.x = _position.x + maxDistance;
				}
			}
		}		
	}
	
	if (moveRight + moveLeft < 0) { // going left
		
		
		// check tiles directly to the left
		
		destination.x = floor(tile.x / ls::getTileSize()) - 1;
		destination.y = floor(tile.y / ls::getTileSize());
		
		max = 0;
		
		while (max == 0 && destination.x >= 0) {
			
			if (ls::getTile(destination) == ls::WALL) {
				max = (destination.x + 1) * ls::getTileSize();
				if (newPos.x < max + 25) {
					newPos.x = max + 25;
				}
			}
			destination.x--;
		}
		
		
		// check upper left tile
		
		if (newPos.y < tile.y) { 
			
			// get top left corner of this tile
			Vector2f vertice = {
				tile.x - ls::getTileSize() / 2, 
				tile.y - ls::getTileSize() / 2
			};
			// calculate maximum available distance from current position
			float sideP = _position.y - vertice.y;
			
			if (sideP < 25) {
				float sideV = sqrt(pow(25.f,2) - pow(sideP,2));
				float maxDistance = _position.x - vertice.x - sideV;

				// update destination if necessary
				if (newPos.x < _position.x - maxDistance) {
					newPos.x = _position.x - maxDistance;
				}
			}		
		}
		
		
		// check lower left tile
		
		if (newPos.y > tile.y) {
		
			// get bottom left corner of this tile
			Vector2f vertice = {
				tile.x - ls::getTileSize() / 2, 
				tile.y + ls::getTileSize() / 2
			};
			// calculate maximum available distance from current position
			float sideP = vertice.y - _position.y;
			
			if (sideP < 25) {
				float sideV = sqrt(pow(25.f,2) - pow(sideP,2));
				float maxDistance = _position.x - vertice.x - sideV;

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