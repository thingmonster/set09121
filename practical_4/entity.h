#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "ecm.h"
#include "system_renderer.h"
#include "cmp_sprite.h"


struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	void render();
};


