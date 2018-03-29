
#include "pacman.h"

using namespace sf;
using namespace std;



std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

shared_ptr<Entity> player;
vector<shared_ptr<Entity>> ghosts;
vector<shared_ptr<Entity>> nibbles;




shared_ptr<Entity> GameScene::makeEntity() {
	auto e = make_shared<Entity>(this);
  _ents.list.push_back(e);
	return e;
}


GameScene::GameScene() : Scene() {cout << "GAMESCENE" << endl;}

void GameScene::update(double dt) {
	
	if (Keyboard :: isKeyPressed(Keyboard :: Tab)) {
		activeScene = menuScene;
	}
	
	bool dead = false;
	for (auto& g : ghosts) {
		if (length(g->getPosition() - player->getPosition()) < 30.0f) {
			respawn();
			dead = true;
		}
	} 
	
	if (!dead) {
		// Scene::update(dt);
		_ents.update(dt);
	}
}

void GameScene::render() {
	_ents.render();
	ls::render(Renderer::getWindow());
}

void GameScene::load() {

	ls::loadLevelFile("res/pacman.txt", 23);
	
	respawn();
	
}

void GameScene::respawn() {
	
	// remove old entities
	
	_ents.list.clear();
	player.reset();
	
	for (auto g : ghosts) {
		g.reset();
	}
	ghosts.clear();
	
	for (auto n : nibbles) {
		n->setForDelete();
		n.reset();
	}
	nibbles.clear();
	
	// add nibbles
	
	auto nibbleLoc = ls::findTiles(ls::EMPTY);
	for (const auto& nl : nibbleLoc) {
		auto cherry = GameScene::makeNibble(nl, false);
		// _ents.list.push_back(cherry);
		nibbles.push_back(cherry);		
	}
	
	nibbleLoc = ls::findTiles(ls::WAYPOINT);
	for (const auto& nl : nibbleLoc) {
		auto cherry = GameScene::makeNibble(nl, true);
		// _ents.list.push_back(cherry);
		nibbles.push_back(cherry);		
	}
	
	
	// add player
	
	
	
	// auto pl = make_shared<Entity>();
	auto pl = GameScene::makeEntity();
	pl->setPosition(ls::getTileCentre(ls::findTiles(ls::START)[0]));
	auto s = pl->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(10.f);
	s->getShape().setFillColor({208 , 62, 25});
	s->getShape().setOrigin(Vector2f(10.f, 10.f));
	auto m = pl->addComponent<PlayerMovementComponent>();
	m->setSpeed(150.f);
	
	// _ents.list.push_back(pl);
	player = pl;
	
	
	// add ghosts
	
	const sf::Color ghost_cols[]{
		{208,62,25},
		{219,133,28},
		{70,191,238},
		{234,130,229}
	};
	
	auto enemies = ls::findTiles(ls::ENEMY);
	
	// for (int i = 0; i < enemies.size(); ++i) {
	for (int i = 0; i < 4; ++i) {
		
		auto ghost = GameScene::makeEntity();
		ghost->setPosition(ls::getTileCentre(ls::findTiles(ls::ENEMY)[i]));
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(10.f);
		s->getShape().setFillColor(ghost_cols[i%4]);
		s->getShape().setOrigin(Vector2f(10.f, 10.f));
		auto m = ghost->addComponent<EnemyMovementComponent>();
		m->setSpeed(100.f);
	
		// _ents.list.push_back(ghost);
		ghosts.push_back(ghost);
		
		
	}

	
	// std::vector<std::shared_ptr<PlayerMovementComponent>> playerComponents = 
		// e->getComponents<PlayerMovementComponent>();
	
	// if (playerComponents.size() > 0) {
		// e->setPosition(ls::getTileCentre(ls::findTiles(ls::START)[0]));
		// e->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);
	// }
	
	// std::vector<std::shared_ptr<EnemyMovementComponent>> enemyComponents = 
		// e->getComponents<EnemyMovementComponent>();
	
	// if (enemyComponents.size() > 0) {
		// e->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.f);
	// }
}

shared_ptr<Entity> GameScene::makeNibble(const Vector2ul& nl, bool big) {
	
	float size;
	if (big) {
		size = 4.f;
	} else {
		size = 2.f;
	}
		
	
	auto cherry = GameScene::makeEntity();
	cherry->addComponent<PickupComponent>(big);
	cherry->setPosition(ls::getTilePosition(nl) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
	
	auto s = cherry->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(size);
	s->getShape().setFillColor({208 , 208, 150});
	s->getShape().setOrigin(Vector2f(size, size));
	
	return cherry;
}

std::vector<std::shared_ptr<Entity>>& Scene::getEnts() {
	return _ents.list;
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






