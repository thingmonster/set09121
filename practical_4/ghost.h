#pragma once
#include "entity.h"

class Ghost : public Entity {
	
	private:
		float _speed;
		float _direction;
	
	public:
		bool update(double dt) override;
		Ghost();
		void render() const override;
		
};