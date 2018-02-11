
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

static int gameWidth = 800;
static int gameHeight = 600;



void reset() {
	
}

void load() {
	
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
	
}

void render(RenderWindow &window) {

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




