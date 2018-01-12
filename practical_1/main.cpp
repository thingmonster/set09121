
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

const  Keyboard ::Key  controls [4] = {
    Keyboard ::A,
    Keyboard ::Z,
    Keyboard ::Up,
    Keyboard ::Down
};



CircleShape ball;
const float ballRadius = 10.f;
Vector2f  ballSpeed;

RectangleShape paddles[2];
const Vector2f paddleSize(25.f, 100.f);
const  float  paddleSpeed = 800.f;

bool server = false;

void reset() {

    ball.setPosition(gameWidth / 2, gameHeight / 2);
//    ball.setPosition(80, 250);
    paddles[0].setPosition(10 + (paddleSize.x / 2), gameHeight / 2);
    paddles[1].setPosition(gameWidth - 10 - (paddleSize.x / 2), gameHeight / 2);

}

void load() {

    ball.setOrigin(ballRadius, ballRadius);
    ball.setFillColor(sf::Color(100, 150, 200));
    ball.setRadius(ballRadius);
    ball.setPointCount(100);
    ballSpeed = {server ? 50.0f : -50.0f, 60.0f};

    paddles[0].setSize(paddleSize);
    paddles[0].setOrigin(paddleSize / 2.f);
    paddles[0].setFillColor(sf::Color::White);

    paddles[1].setSize(paddleSize);
    paddles[1].setOrigin(paddleSize / 2.f);
    paddles[1].setFillColor(sf::Color::White);

    reset();

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



    float direction = 0.f;
    if ((Keyboard::isKeyPressed(controls[0])) && (paddles[0].getPosition().y > 10 + (paddleSize.y / 2))) {
        direction--;
    }
    if ((Keyboard::isKeyPressed(controls[1])) && (paddles[0].getPosition().y < gameHeight - 10 - (paddleSize.y / 2))) {
        direction++;
    }
    paddles[0].move(0, direction * paddleSpeed * dt);

    float direction2 = 0.f;
    if (Keyboard::isKeyPressed(controls[2])) {
        direction2--;
    }
    if (Keyboard::isKeyPressed(controls[3])) {
        direction2++;
    }
    paddles[1].move(0, direction2 * paddleSpeed * dt);




    ball.move(ballSpeed * dt);
    const  float  bx = ball.getPosition ().x;
    const  float  by = ball.getPosition ().y;

    if (by > gameHeight - ballRadius) {
        ballSpeed.x *= 1.1f;
        ballSpeed.y *= -1.1f;
    } else if (by < ballRadius) {
        ballSpeed.x *= 1.1f;
        ballSpeed.y *= -1.1f;
    }

    if ((bx > gameWidth - ballRadius) || (bx < ballRadius)) {
        load();
    } else {

        if (
            (
                (bx < 10 + paddleSize.x + ballRadius) &&
                (by > paddles[0].getPosition().y - (paddleSize.y * .5)) &&
                (by < paddles[0].getPosition().y + (paddleSize.y * .5))
            ) || (
                (bx > gameWidth - 10 - paddleSize.x - ballRadius) &&
                (by > paddles[1].getPosition().y - (paddleSize.y * .5)) &&
                (by < paddles[1].getPosition().y + (paddleSize.y * .5))
            )
        ) {

            ballSpeed.x *= -1.1f;
            ballSpeed.y *= 1.1f;

        }


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









