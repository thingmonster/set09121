#pragma once
#include "entity.h"
#include "ecm.h"

class Player : public Entity {
	
	private:
		float _speed;
		double _momentum(double * timer);
	
	public:
		void update(double dt) override;
		Player();
		void render() override;
		
};