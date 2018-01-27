#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
	
	public:
		Bullet();
		void Fire(sf::Vector2f &pos, bool mode);
		static Bullet bullets[256];
		void Update(const float &dt);
		bool getVisibility();
		static unsigned char getBulletPointer();
	protected:
		sf::IntRect _sprite;
		static unsigned char bulletPointer;
		bool visible;
		bool _mode;
};

extern Bullet bullets[256];
extern std::vector<Ship *> ships;
