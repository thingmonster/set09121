#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "ecm.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_player_movement.h"


struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	void render();
};


