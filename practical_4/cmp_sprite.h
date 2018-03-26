
#pragma once
#include "entity.h"
#include "ecm.h"
#include <SFML/Graphics.hpp>

class ShapeComponent : public Component {
	
	protected:
		std::shared_ptr<sf::Shape> _shape;
		// Entity * _parent;
	
	public:
		ShapeComponent() = delete;
		explicit ShapeComponent(Entity *p);
		
		void update(double dt) override;
		void render() override;
		sf::Shape &getShape() const;
		
		template <typename T, typename... Targs>
		void setShape(Targs... params) {
			_shape.reset(new T(params...));
		}
};








