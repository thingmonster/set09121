#pragma once
#include "game.h"
#include "entity.h"

class Player : public Entity {
	
	private:
		float _speed;
		float _momentum(float * timer);
	
	public:
		void update(double dt) override;
		Player();
		void render(sf::RenderWindow &window) const override;
		
};