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
class Scene;

class Entity {
	
	protected:
		sf::Vector2f _position;
		float _radius;
		bool _fordeletion;
		
	public:
		Entity(Scene* s);
		~Entity() = default;
		Scene* const scene;
		void update(const double dt);
		void render();
		const sf::Vector2f getPosition();
		void setPosition(const sf::Vector2f &pos);
		void move(const sf::Vector2f &pos);
		float getRadius();
		void setForDelete();
		bool is_fordeletion();
		std::vector<std::shared_ptr<Component>> _components;
		
	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}

	template <typename T>
	const std::vector<std::shared_ptr<T>> getComponents() const {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (const auto c : _components) {
			if (typeid(*c) == typeid(T)) {
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return std::move(ret);
	}
	
	template <typename T>
	const std::vector<std::shared_ptr<T>> GetCompatibleComponent() {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (auto c : _components) {
			auto dd = dynamic_cast<T*>(&(*c));
			if (dd) {
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return ret;
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

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	void render();
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
 
 
 
 