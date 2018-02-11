
#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "ghost.h"

using namespace sf;
using namespace std;

std::vector<Entity *> entities;

static int gameWidth = 800;
static int gameHeight = 600;



void reset() {
	
}

void load() {
	
	
	Player* p = new Player();
	entities.push_back(p);
	
	for (int i = 0; i < 4; i++) {
		Ghost* g = new Ghost();
		entities.push_back(g);
	}
}

void update(RenderWindow &window) {

	static sf::Clock clock;
	const float dt = clock.restart().asSeconds();
	
	sf::Event event;
	while (window.pollEvent(event))
	{
			if (event.type == sf::Event::Closed)
					window.close();
	}

	if (Keyboard :: isKeyPressed(Keyboard :: Escape)) {
			window.close();
	}
	
	for (auto &e : entities) {
		e->update(dt);
	}

}

void render(RenderWindow &window) {

	for (auto &e : entities) {
		e->render(window);
	}

	
}

int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	load();
	
	sf::RenderWindow window(sf::VideoMode(gameWidth,gameHeight), "Pacman");
	window.setVerticalSyncEnabled(true);
	
	while (true) {

		window.clear();
		update(window);
		render(window);
		window.display();

	}

	return 0;
}




