#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
	
	public:
		Bullet();
		void Fire(sf::Vector2f &pos);
		static Bullet bullets[256];
		void Update(const float &dt);
		bool getVisibility();
		static unsigned char getBulletPointer();
	protected:
		sf::IntRect _sprite;
		static unsigned char bulletPointer;
		bool visible;
};

extern Bullet bullets[256];
