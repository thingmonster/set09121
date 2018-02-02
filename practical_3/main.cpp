
#include <iostream>
#include <SFML/Graphics.hpp>
#include "levelsystem.h"
#include "game.h"
#include "entity.h"
#include "player.h"

using namespace sf;
using namespace std;

std::vector<Entity *> entities;

void reset() {

}

void load() {
	
	Player* p = new Player();
	entities.push_back(p);
	
	ls::loadLevelFile("res/maze_2.txt");
	
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			// cout << ls::getTile({x, y});
		}
		cout << endl;
		
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
	
	entities[0]->update(dt);

}

void render(RenderWindow &window) {

	entities[0]->render(window);
	ls::render(window);
}


int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(gameWidth,gameHeight), "Maze");
    window.setVerticalSyncEnabled(true);
    load();


    while (true) {

        window.clear();
        update(window);
        render(window);
        window.display();

    }


    return 0;
}















