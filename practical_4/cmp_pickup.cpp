

#include "cmp_pickup.h"



using namespace sf;
using namespace std;

void PickupComponent::update(double dt) {
	for (auto& e : _parent->scene->getEnts()) {
		if (length(_parent->getPosition() - e->getPosition()) < 10.0f) {
			
			std::vector<std::shared_ptr<ActorMovementComponent>> components = 
			e->GetCompatibleComponent<ActorMovementComponent>();
			
			if (components.size() > 0) {
				_parent->setForDelete();
				break;
			}
			
		}
	} 
}

void PickupComponent::render() {}

PickupComponent::PickupComponent(Entity *p, bool big) : Component(p) {
	if (big) {
		points = 1;
	} else {
		points = 2;
	}
}







