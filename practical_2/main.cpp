
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "ship.h"

using namespace sf;
using namespace std;

sf::Texture spritesheet;
std::vector<Ship *> ships;


void reset() {

}

void load() {
 
	if (!spritesheet.loadFromFile("res/ss.jpg"))
	{
		// error...
	}
	
	for (float r = 0; r < invaders_rows; r++) {
		auto rect = sf::IntRect(r*32, r*32, 32, 32);	
		for (float c = 0; c < invaders_columns; c++) {
			Vector2f position = {c*40,r*40};
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}
	
}

void update(RenderWindow &window) {

    static sf::Clock clock; // should this go here?
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
	
	for (auto &s : ships) {
		s->Update(dt);
	}

}

void render(RenderWindow &window) {

	for (const auto &s : ships) {
		window.draw(*s);
	}

}


int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(gameWidth,gameHeight), "Space Invaders");
    window.setVerticalSyncEnabled(true); // does this go here?
    load();


    while (true) {

        window.clear();
        update(window);
        render(window);
        window.display();

    }


    return 0;
}















