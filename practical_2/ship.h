#pragma once
#include <SFML/Graphics.hpp>


class Ship : public sf::Sprite {
	protected:
		sf::IntRect _sprite;
		Ship();
	public:
		explicit Ship(sf::IntRect ir);
		virtual ~Ship() = 0;
		virtual void Update(const sf::RenderWindow &window, const float &dt);
};

 
class Invader : public Ship {
	public:
		Invader(sf::IntRect ir, sf::Vector2f pos);
		Invader();
		void Update(const sf::RenderWindow &window, const float &dt) override;
		static bool direction;
		static float speed;
	
};

class Player : public Ship {
	public:
		Player();
		void Update(const sf::RenderWindow &window, const float &dt) override;
};


extern std::vector<Ship *> ships;