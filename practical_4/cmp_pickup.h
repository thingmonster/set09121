
#pragma once
#include "scene.h"

class PickupComponent : public Component {
	
	public:
		PickupComponent() = delete;
		explicit PickupComponent(Entity *p, bool big);
		
		void update(double dt) override;
		void render() override;
		
		int points;
		
};








