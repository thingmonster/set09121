#pragma once
#include "maths.h"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Component;

class Entity {
	
	protected:
		// std::unique_ptr<sf::Shape> _shape;
		sf::Vector2f _position;
		Entity(std::unique_ptr<sf::Shape> shp);
		float _radius;
		
	public:
		Entity();
		~Entity() = default;
		void update(const double dt);
		void render();
		const sf::Vector2f getPosition();
		void setPosition(const sf::Vector2f &pos);
		void move(const sf::Vector2f &pos);
		float getRadius();
		std::vector<std::shared_ptr<Component>> _components;
		
	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}

	
	
};




class Component {
	
	protected:
		Entity * _parent;
		bool _fordeletion;
		explicit Component(Entity *const p);
		
	public:
		Component() = delete;
		virtual ~Component() = default; // won't compile without default
		
		bool is_fordeletion() const;
		virtual void update(double dt) = 0;
		virtual void render() = 0;
		
};





/* SAM'S EXAMPLE:

class Component;

class Entity {
	
	protected:
		// std::vector<std::shared_ptr<Component>> _components;
		// sf::Vector2f _position;
		// float _rotation;
		// bool _alive;
		// bool _visible;
		// bool _fordeletion;
		
	public:
		Entity();
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
 
 
 
 