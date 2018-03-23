
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ecm.h"
#include "entity.h"
#include "system_renderer.h"
#include "player.h"
#include "ghost.h"
#include "scene.h"
#include "pacman.h"


using namespace sf;
using namespace std;

static int gameWidth = 800;
static int gameHeight = 600;

void reset() {
	
}

void load() {
		
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	
	gameScene->load();
	menuScene->load();
	
	activeScene = menuScene;
	
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
	
	activeScene->update(dt);
	
}

void render(RenderWindow &window) {

	activeScene->render();
	Renderer::render();
}

int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	load();
	
	sf::RenderWindow window(sf::VideoMode(gameWidth,gameHeight), "Pacman");
	window.setVerticalSyncEnabled(true);
	Renderer::initialise(window);
	
	while (true) {

		window.clear();
		update(window);
		render(window);
		window.display();

	}

	return 0;
}




