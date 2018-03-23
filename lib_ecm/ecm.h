#pragma once
#include "maths.h"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Entity {
	
	protected:
		std::unique_ptr<sf::Shape> _shape;
		sf::Vector2f _position;
		Entity(std::unique_ptr<sf::Shape> shp);
		float _radius;
		
	public:
		Entity() = delete;
		virtual ~Entity() = default;
		virtual void update(const double dt);
		virtual void render() = 0;
		const sf::Vector2f getPosition();
		void setPosition(const sf::Vector2f &pos);
		void move(const sf::Vector2f &pos);
		float getRadius();
		
};

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	void render();
};


/* SAM'S EXAMPLE:

class Component;

class ECM {
	
	protected:
		// std::vector<std::shared_ptr<Component>> _components;
		// sf::Vector2f _position;
		// float _rotation;
		// bool _alive;
		// bool _visible;
		// bool _fordeletion;
		ECM(std::unique_ptr<sf::Shape> shp);
		
	public:
		ECM();
		virtual void update(double dt);
		virtual void render();
		// const sf::Vector2f &getPosition() const;
		// void setPosition(const sf::Vector2f &_position);
		// bool is_fordeletion() const;
		// float getRotation() const;
		// void setRotation(float _rotation);
		// bool is_alive();
		// void setAlive(bool _alive);
		// void setForDelete();
		// bool isVisible() const;
		// void setVisible(bool _visible);
		
};

 */
 
 
 
 