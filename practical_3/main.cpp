
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>
#include "levelsystem.h"
#include "entity.h"
#include "player.h"

using namespace sf;
using namespace std;


sf::Font font;
sf::Text yourTimeWas;
sf::Text previousBest;
sf::Text pressEnter;

std::vector<Entity *> entities;

bool running = false;

static sf::Clock playerTimer;
float yourTime;

static int gameWidth;
static int gameHeight;



void reset() {
	
	running = true;
	
	entities[0]->setPosition(ls::getTileCoordinates(ls::START));
	
	yourTime = playerTimer.restart().asSeconds();
	
}

void stopGame() {
	
	// get time to reach end
	
	yourTime = playerTimer.restart().asSeconds();
		
	stringstream stream;
	stream << fixed << setprecision(2) << yourTime;
	string yourTimeString = stream.str();

	// get previous best from file
	
	string best;
	bool fileExists = false;
	bool overWrite = false;
	
  ifstream myfile ("tile-save-test.txt");
	
  if (myfile.is_open()) {
    while (getline(myfile, best)) {
			fileExists = true;
			float bestFloat = std::stof(best);
			if (yourTime < bestFloat) {
				overWrite = true;
			}
		}
    myfile.close();
  } else {
		cout << "Unable to open file"; 
	}

	// save new time if appropriate
	
	if ((overWrite) || (!fileExists)) {
		ofstream myfiles;
		myfiles.open ("tile-save-test.txt");
		myfiles << yourTimeString;
		myfiles.close();
	}	
	
	
	
	// write current time and previous best if it exists
	
	yourTimeWas.setString("Your time was " + yourTimeString + " seconds");
	yourTimeWas.setPosition(
		(gameWidth * 0.5f) - (yourTimeWas.getLocalBounds().width * 0.5f), 
		(gameHeight / 8)
	);
	
	if (fileExists) {
			
		if (overWrite) {
			previousBest.setString("Your previous best was " + best + " seconds");
		} else {
			previousBest.setString("Your best time was " + best + " seconds");
		}
		
		previousBest.setPosition(
			(gameWidth * 0.5f) - (previousBest.getLocalBounds().width * 0.5f), 
			(gameHeight / 8) + yourTimeWas.getLocalBounds().height + 30
		);
	}
	
	running = false;
		
}

void load() {
	
	ls::loadLevelFile("res/maze_2.txt");
	gameWidth = ls::getWidth() * ls::getTileSize();
	gameHeight = ls::getHeight() * ls::getTileSize();
	
	font.loadFromFile("res/fonts/Rubik-Medium.ttf");
	
	yourTimeWas.setFont(font);
	yourTimeWas.setCharacterSize(50);
	yourTimeWas.setColor(sf::Color(130,145,160));
	
	previousBest.setFont(font);
	previousBest.setCharacterSize(30);
	previousBest.setColor(sf::Color(130,145,160));
	
	pressEnter.setFont(font);
	pressEnter.setCharacterSize(55);
	pressEnter.setColor(sf::Color(130,145,160));
	pressEnter.setString("Press enter to play again");
	pressEnter.setPosition(
		(gameWidth * 0.5f) - (pressEnter.getLocalBounds().width * 0.5f), 
		gameHeight - pressEnter.getLocalBounds().height - 50
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
			stopGame();
		}
		
	} else {
		
			
		if (Keyboard :: isKeyPressed(Keyboard :: Return)) {
			reset();
		}
	
	}
}

void render(RenderWindow &window) {

	if (running) {
		ls::render(window);
		entities[0]->render(window);
	} else {
		window.draw(yourTimeWas);
		window.draw(previousBest);
		window.draw(pressEnter);
	}
}

int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	load();
	
	sf::RenderWindow window(sf::VideoMode(gameWidth,gameHeight), "Maze");
	window.setVerticalSyncEnabled(true);
	
	running = true;
	
	while (true) {

		window.clear();
		update(window);
		render(window);
		window.display();

	}

	return 0;
}




