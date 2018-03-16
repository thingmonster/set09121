#include <iostream>	
#include "pacman.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;



std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;



GameScene::GameScene() : Scene() {cout << "GAMESCENE" << endl;}
void GameScene::update(double dt) {cout << "update" << endl;}
void GameScene::render() {cout << "render" << endl;}
void GameScene::load() {cout << "load" << endl;}






