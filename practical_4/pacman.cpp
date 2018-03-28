#include <iostream>	
#include <SFML/Graphics.hpp>
#include "pacman.h"
#include "system_renderer.h"

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
	ls::render(Renderer::getWindow());
}

void GameScene::load() {

	ls::loadLevelFile("res/pacman.txt", 23);
	
	auto pl = make_shared<Entity>();
	
	auto s = pl->addComponent<ShapeComponent>();
	auto m = pl->addComponent<PlayerMovementComponent>();
	s->setShape<sf::CircleShape>(10.f);
	s->getShape().setFillColor({208 , 62, 25});
	s->getShape().setOrigin(Vector2f(10.f, 10.f));
	_ents.list.push_back(pl);
	
	GameScene::respawn(pl);
	
	const sf::Color ghost_cols[]{
		{208,62,25},
		{219,133,28},
		{70,191,238},
		{234,130,229}
	};
	
	auto enemies = ls::findTiles(ls::ENEMY);
	
	// for (int i = 0; i < enemies.size(); ++i) {
	for (int i = 0; i < 4; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		auto m = ghost->addComponent<EnemyMovementComponent>();
		s->setShape<sf::CircleShape>(10.f);
		s->getShape().setFillColor(ghost_cols[i%4]);
		s->getShape().setOrigin(Vector2f(10.f, 10.f));
		_ents.list.push_back(ghost);
		GameScene::respawn(ghost);
		
		ghost->setPosition(ls::getTileCentre(ls::findTiles(ls::ENEMY)[i]));
	}

	
	
}

void GameScene::respawn(std::shared_ptr<Entity> e) {
	
	std::vector<std::shared_ptr<PlayerMovementComponent>> playerComponents = 
		e->getComponents<PlayerMovementComponent>();
	
	if (playerComponents.size() > 0) {
		e->setPosition(ls::getTileCentre(ls::findTiles(ls::START)[0]));
		e->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);
	}
	
	std::vector<std::shared_ptr<EnemyMovementComponent>> enemyComponents = 
		e->getComponents<EnemyMovementComponent>();
	
	if (enemyComponents.size() > 0) {
		e->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.f);
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






