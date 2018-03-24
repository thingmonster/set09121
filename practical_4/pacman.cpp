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
	
	cout << "GS update" << endl;
	
	if (Keyboard :: isKeyPressed(Keyboard :: Tab)) {
		activeScene = menuScene;
	}
	
	// Scene::update(dt);
	em.update(dt);
}

void GameScene::render() {
	em.render();
}

void GameScene::load() {

	shared_ptr<Entity> p(new Player());	
	em.list.push_back(p);
	
	for (int i = 0; i < 4; i++) {
		shared_ptr<Entity> g(new Ghost());
		em.list.push_back(g);
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






