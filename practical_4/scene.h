

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "ecm.h"
#include "levelsystem.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_player_movement.h"
#include "cmp_enemy_movement.h"
#include "cmp_pickup.h"
#include "system_renderer.h"

class Scene {
	
	public:
		Scene() = default;
		virtual ~Scene() = default;
		virtual void update(double dt) = 0;
		virtual void render() = 0;
		virtual void load() = 0;
		std::vector<std::shared_ptr<Entity>> &getEnts();
		
	protected:
		EntityManager _ents;
};









