#pragma once
#include "cmp_actor_movement.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class EnemyMovementComponent : public ActorMovementComponent {
	
	private:
		sf::Vector2i _direction;
		enum state { DEADEND, STARTING, ROAMING, ROTATING, ROTATED };
		state _state;
		void roaming(float mva);
		void rotating(float mva);
		void rotated(float mva);
		
	public:
		EnemyMovementComponent() = delete;
		explicit EnemyMovementComponent(Entity *p);
		void update(double dt) override;
	
};