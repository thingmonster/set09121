
#include <iostream>
#include "entity.h"

using namespace sf;
using namespace std;



void EntityManager::update(double dt) {
	
	for (auto &e : list) {
		for (auto &c : e->_components) {
			c->update(dt);
		}
	}
}
	
void EntityManager::render() {
	for (auto &e : list) {
		for (auto &c : e->_components) {
			c->render();
		}
	}
}
	
	
	
	
	
	
	
	
	