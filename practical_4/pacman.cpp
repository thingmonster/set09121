#include <iostream>	
#include <SFML/Graphics.hpp>
#include "pacman.h"
#include "system_renderer.h"

#define GHOSTS_COUNT 4

using namespace sf;
using namespace std;



std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

EntityManager em;



GameScene::GameScene() : Scene() {cout << "GAMESCENE" << endl;}

void GameScene::update(double dt) {
	
	if (Keyboard :: isKeyPressed(Keyboard :: Tab)) {
		activeScene = menuScene;
	}
	
	// Scene::update(dt);
	_ents.update(dt);
}

void GameScene::render() {
	_ents.render();
}

void GameScene::load() {

	static sf::Clock clock;
	const float asd = clock.restart().asSeconds();

	auto pl = make_shared<Entity>();
	pl->setPosition(Vector2f(400.f, 400.f));
	
	auto s = pl->addComponent<ShapeComponent>();
	auto m = pl->addComponent<PlayerMovementComponent>();
	s->setShape<sf::CircleShape>(12.f);
	s->getShape().setFillColor({208 , 62, 25});
	s->getShape().setOrigin(Vector2f(12.f, 12.f));
	_ents.list.push_back(pl);
	
	
	const sf::Color ghost_cols[]{
		{208,62,25},
		{219,133,28},
		{70,191,238},
		{234,130,229}
	};
	
	for (int i = 0; i < GHOSTS_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		auto m = ghost->addComponent<EnemyMovementComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i%4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));
		ghost->setPosition(Vector2f(i*50.f, i*50.f));
		_ents.list.push_back(ghost);
	}

	
}



MenuScene::MenuScene() : Scene() {}

void MenuScene::update(double dt) {
	
	
	if (Keyboard :: isKeyPressed(Keyboard :: Space)) {
		activeScene = gameScene;
	}
	
	// Scene::update(dt);
}

void MenuScene::render() {
	Renderer::queue(&text);
	
}

void MenuScene::load() {

	
	font.loadFromFile("res/fonts/Rubik-Medium.ttf");
	
	text.setFont(font);
	text.setCharacterSize(55);
	text.setColor(sf::Color(130,145,160));
	text.setString("Could have been PACMAN");
	text.setPosition(10, 10);
	
}






