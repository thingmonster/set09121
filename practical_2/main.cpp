
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


int gameWidth = 800;
int gameHeight = 600;
int invaders_rows = 5;
int invaders_columns = 12;

sf::Texture spritesheet;


class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	Ship();
public:
	explicit Ship(sf::IntRect ir);
	virtual ~Ship() = 0;
	virtual void Update(const float &dt);
};

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
}

void Ship::Update(const float &dt) {}

Ship::~Ship() = default;


 
class Invader : public Ship {
public:
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float &dt) override;
};


Invader::Invader() : Ship() {}
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	Ship::Update(dt);
}


void reset() {

}

void load() {
 
	if (!spritesheet.loadFromFile("res/ss.jpg"))
	{
		// error...
	}
	
	Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100,100 });

}

void update(RenderWindow &window) {

    static sf::Clock clock; // should this go here?
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

    sf::RenderWindow window(sf::VideoMode(gameWidth,gameHeight), "Space Invaders");
    window.setVerticalSyncEnabled(true); // does this go here?
    load();


    while (true) {

        window.clear();
        update(window);
        render(window);
        window.display();

    }


    return 0;
}


