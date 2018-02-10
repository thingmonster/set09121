#pragma once
#include "game.h"
#include "entity.h"

class Player : public Entity {
	
	private:
		float _speed;
		double _momentum(double * timer);
	
	public:
		bool update(double dt) override;
		Player();
		void render(sf::RenderWindow &window) const override;
		
};