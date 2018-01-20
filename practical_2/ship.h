#pragma once
#include <SFML/Graphics.hpp>


class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	Ship();
public:
	explicit Ship(sf::IntRect ir);
	virtual ~Ship() = 0;
	virtual void Update(const float &dt);
};

 
class Invader : public Ship {
public:
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float &dt) override;
	static bool direction;
	static float speed;
};

// void Invader::Update(const float &dt) {
	
	// Ship::Update(dt);
	
	// move(dt * (direction ? 1.0f : -1.0f) * speed, 0);
	
	// if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
		// direction = !direction;
		// for (int i = 0; i < 1; ++i) {
			// ships[i]->move(0, 24);
		// }
	// }
// }
extern std::vector<Ship *> ships;