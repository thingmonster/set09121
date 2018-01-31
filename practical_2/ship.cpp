
#include <iostream>
#include "game.h"
#include "ship.h"
#include "bullet.h"

using namespace sf;
using namespace std;

bool Invader::direction = false;
float Invader::speed = 100;

const Keyboard::Key controls[] = {
    Keyboard::Left,
    Keyboard::Right,
    Keyboard::Up
};






Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
	_exploded = false;
	visible = true;
}

void Ship::Update(const sf::RenderWindow &window, const float &dt) {}

void Ship::explode(const float &dt) {
	
	setTextureRect(IntRect(128,32,32,32));
	
	static float timeofdeath = 0.0f;
		
	if (!_exploded) {
		_exploded = true;
		timeofdeath = .5f;
			cout << "x  " << visible << endl;
	}
	
	if (visible) {		
		timeofdeath -= dt;
		cout << timeofdeath << endl;
		if (timeofdeath < 0) {
			cout << "hi";
			visible = false;
		}
	}
}

Ship::~Ship() = default;

bool Ship::is_exploded() const {
	return _exploded;
}





Invader::Invader() : Ship() {}
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
	direction = true;
}

void Invader::Update(const sf::RenderWindow &window, const float &dt) {
	
	Ship::Update(window, dt);
	
	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);
	
	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 1; i < ships.size(); i++) {
			ships[i]->move(0, 24);
		}
	}
	
	if (is_exploded() && visible) {
		explode(dt);
	}

	static float fireTime = 0.0f;
	fireTime -= dt;
	
	if (fireTime <= 0 && rand() % 100 == 0) {
		
		sf::Vector2f pos = getPosition();
		bullets[Bullet::getBulletPointer()].Fire(pos, true);
		fireTime = .4f + rand() % 60;
	}
	
}





Player::Player() : Ship(IntRect (160,32,32,32)) {
	setPosition({gameHeight * .5f, gameHeight - 32.f});
	setOrigin(16,16);
}

void Player::Update(const sf::RenderWindow &window, const float &dt) {
	
	Ship::Update(window, dt);
	
	if (is_exploded()) {	
		if (visible) {
			explode(dt);
		}
	} else {
		
		static float fireTime = 0.0f;
		fireTime -= dt;
		
		if (fireTime <= 0 && Keyboard::isKeyPressed(controls[2])) {		
			
			sf::Vector2f pos = getPosition();
			bullets[Bullet::getBulletPointer()].Fire(pos, false);
			fireTime = .7f;
		
		}
		

		int direction = 0;
		
		if ((Keyboard::isKeyPressed(controls[0])) && (getPosition().x > 20)) {
			direction--;
		}

		if ((Keyboard::isKeyPressed(controls[1])) && (getPosition().x < gameWidth - 20)) {
			direction++;
		}

		move(direction * dt * 400, 0);

	}
}




