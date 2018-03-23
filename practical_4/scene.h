

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "entity.h"
#include "ecm.h"
#include "player.h"
#include "ghost.h"

class Scene {
	
	protected:
		
	public:
		Scene() = default;
		virtual ~Scene() = default;
		virtual void update(double dt) = 0;
		virtual void render() = 0;
		virtual void load() = 0;
		std:: vector<std::shared_ptr<Entity>> &getEnts();
		
	protected:
		EntityManager _ents;
};









