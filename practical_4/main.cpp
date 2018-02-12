
#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "ghost.h"

using namespace sf;
using namespace std;



static int gameWidth = 800;
static int gameHeight = 600;

EntityManager em;


void reset() {
	
}

void load() {
	
	shared_ptr<Entity> p(new Player());	
	em.list.push_back(p);
	
	for (int i = 0; i < 4; i++) {
		shared_ptr<Entity> g(new Ghost());	
		em.list.push_back(g);
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
	
	em.update(dt);
	
}

void render(RenderWindow &window) {

	em.render(window);
	
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




