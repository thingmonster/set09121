
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "ship.h"
#include "bullet.h"

using namespace sf;
using namespace std;

sf::Texture spritesheet;
std::vector<Ship *> ships;
Bullet bullets[256];

		
void reset() {

}

void load() {
	
	if (!spritesheet.loadFromFile("res/invaders_sheet.png"))
	{
		cout << "error loading file" << endl;
	}
	
	Player* p = new Player();
	ships.push_back(p);
	
	for (float r = 0; r < invaders_rows; r++) {
		
		auto rect = sf::IntRect(r*32, 0, 32, 32);	
		
		for (float c = 0; c < invaders_columns; c++) {
			Vector2f position = {c*40,r*40+40};
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
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

	for (auto &s : ships) {
		s->Update(window, dt);
	}

	for (Bullet &b : bullets) {
		b.Update(dt);
	}

}

void render(RenderWindow &window) {

	for (const auto &s : ships) {
		if (s->visible) {
			window.draw(*s);
		}
	}
	
	for (Bullet s : bullets) {
		if (s.getVisibility()) {
			window.draw(s);
		}
	}
	

}


int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(gameWidth,gameHeight), "Space Invaders");
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















