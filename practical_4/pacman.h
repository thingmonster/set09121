#pragma once
#include "ecm.h"
#include "scene.h"
#include "system_renderer.h"
#include "cmp_sprite.h"

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class GameScene : public Scene {
	
	private:
		sf::Text text;
		sf::Clock scoreClock;
		void respawn();
		
	
	public:
		GameScene();
		void update(double dt) override;
		void render() override;
		void load() override;
		
};


class MenuScene : public Scene {
	
	private:
		sf::Text text;
		sf::Font font;
		
	public:
		MenuScene();
		void update(double dt) override;
		void render() override;
		void load() override;

};


