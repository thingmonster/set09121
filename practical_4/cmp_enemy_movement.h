#pragma once
#include "cmp_actor_movement.h"

class EnemyMovementComponent : public ActorMovementComponent {
	
	private:
		float _direction;
		
	public:
		EnemyMovementComponent() = delete;
		explicit EnemyMovementComponent(Entity *p);
		void update(double dt) override;
	
};