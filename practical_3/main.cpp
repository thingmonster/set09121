
#include <iostream>
#include <SFML/Graphics.hpp>
#include "levelsystem.h"
#include "game.h"
#include "entity.h"
#include "player.h"

using namespace sf;
using namespace std;


sf::Font font;
sf::Text youWin;
sf::Text pressEnter;

std::vector<Entity *> entities;

bool running = false;




void reset() {
	
	entities[0]->setPosition(ls::getTileCoordinates(ls::START));
	
}

void load() {
	
	ls::loadLevelFile("res/maze_2.txt");
	
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({x, y});
		}
		cout << endl;
		
	}
			
	font.loadFromFile("res/fonts/Rubik-Medium.ttf");
	
	
	youWin.setFont(font);
	youWin.setCharacterSize(50);
	youWin.setColor(sf::Color(130,145,160));
	youWin.setString("You Win");
	youWin.setPosition(
		(gameWidth * 0.5f) - (youWin.getLocalBounds().width * 0.5f), 
		(gameHeight / 3) - youWin.getLocalBounds().height
	);
	
	pressEnter.setFont(font);
	pressEnter.setCharacterSize(50);
	pressEnter.setColor(sf::Color(130,145,160));
	pressEnter.setString("Press enter to play again");
	pressEnter.setPosition(
		(gameWidth * 0.5f) - (pressEnter.getLocalBounds().width * 0.5f), 
		(gameHeight / 3) + pressEnter.getLocalBounds().height
	);
	
	Player* p = new Player();
	entities.push_back(p);
	
	reset();
	
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
	
	if (running) {
		
		if (!entities[0]->update(dt)) {
			running = false;
		}
		
	} else {
		
			
		if (Keyboard :: isKeyPressed(Keyboard :: Return)) {
			reset();
			running = true;
		}
	
	}
}

void render(RenderWindow &window) {

	if (running) {
		ls::render(window);
		entities[0]->render(window);
	} else {
		window.draw(youWin);
		window.draw(pressEnter);
	}
}

int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(gameWidth,gameHeight), "Maze");
	window.setVerticalSyncEnabled(true);
	load();
	
	running = true;
	
	while (true) {

		window.clear();
		update(window);
		render(window);
		window.display();

	}

	return 0;
}




