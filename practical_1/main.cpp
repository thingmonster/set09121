
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

CircleShape ball;
const float ballRadius = 10.f;

RectangleShape paddles[2];
const Vector2f paddleSize(25.f, 100.f);

void load() {

    ball.setOrigin(ballRadius, ballRadius);
    ball.setFillColor(sf::Color(100, 150, 200));
    ball.setRadius(ballRadius);
    ball.setPointCount(100);
    ball.setPosition(gameWidth / 2, gameHeight / 2);

    paddles[0].setSize(paddleSize);
    paddles[0].setOrigin(paddleSize / 2.f);
    paddles[0].setPosition(25.f, 300.f);
    paddles[0].setFillColor(sf::Color::White);

    paddles[1].setSize(paddleSize);
    paddles[1].setOrigin(paddleSize / 2.f);
    paddles[1].setPosition(gameWidth - 25.f, gameHeight / 2);
    paddles[1].setFillColor(sf::Color::White);

}

void update(RenderWindow &window) {

    // get time since last called
    static sf::Clock clock; // should this go here?
    const float dt = clock.restart().asSeconds();

    // check events
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void render(RenderWindow &window) {

    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);

}

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(gameWidth,gameHeight), "SFML!");
    window.setVerticalSyncEnabled(true); // does this go here?
    load();


    // graphics card nearly dead, close automatically after a couple of seconds
    int x = 0;
    while (x < 100) {

        x++;

        window.clear();
        update(window);
        render(window);
        window.display();

    }


    return 0;
}









