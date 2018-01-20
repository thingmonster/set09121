
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "ship.h"

using namespace sf;
using namespace std;

sf::Texture spritesheet;



void reset() {

}

void load() {
 
	if (!spritesheet.loadFromFile("res/ss.jpg"))
	{
		// error...
	}
	
	Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100,100 });

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

}

void render(RenderWindow &window) {

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


