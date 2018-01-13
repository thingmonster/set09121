
#include <iostream>
#include <sstream>
#include <string>
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
const  float  paddleSpeed = 400.f;

bool server = false;

string ai_movement;
string ballDirection;

sf::Font font;
sf::Text text;
sf::Font yearFont;
sf::Text yearText;
sf::Font scoreFont;
sf::Text scoreText;

int playerScore = 0;
int AIScore = 0;



void reset() {

    if (playerScore + AIScore > 0) {

        stringstream scores;
        scores << "Player " << playerScore << "      Computer " << AIScore;
        scoreText.setString(scores.str());
        scoreText.setPosition((gameWidth * 0.5f) - (scoreText.getLocalBounds().width * 0.5f), gameHeight - 40);
        cout << scoreText.getLocalBounds().height << endl;
    }

    ballSpeed = {server ? 200.0f : -200.0f, 260.0f};
    ballDirection = {server ? "right" : "left"};
    ball.setPosition(gameWidth / 2, gameHeight / 2);
    ball.setPosition(100,100);
    paddles[0].setPosition(10 + (paddleSize.x / 2), gameHeight / 2);
    paddles[1].setPosition(gameWidth - 10 - (paddleSize.x / 2), gameHeight / 2);

}

void load() {

    font.loadFromFile("../res/fonts/Hawaii_Killer.ttf");
    text.setFont(font);
    text.setCharacterSize(120);
    text.setColor(sf::Color(30,45,60));
    text.setString("Epic Pong Battle");
    text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), (gameHeight / 3) - text.getLocalBounds().height);

    yearFont.loadFromFile("../res/fonts/AngelicWar.ttf");
    yearText.setFont(yearFont);
    yearText.setCharacterSize(200);
    yearText.setColor(sf::Color(30,45,60));
    yearText.setString("2018!!");
    yearText.setPosition((gameWidth * 0.5f) - (yearText.getLocalBounds().width * 0.5f), (gameHeight / 3));

    scoreFont.loadFromFile("../res/fonts/bummer.ttf");
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(24);
    scoreText.setColor(sf::Color(80, 120, 150));

    ball.setOrigin(ballRadius, ballRadius);
    ball.setFillColor(sf::Color(100, 150, 200));
    ball.setRadius(ballRadius);
    ball.setPointCount(100);

    paddles[0].setSize(paddleSize);
    paddles[0].setOrigin(paddleSize / 2.f);
    paddles[0].setFillColor(sf::Color::White);

    paddles[1].setSize(paddleSize);
    paddles[1].setOrigin(paddleSize / 2.f);
    paddles[1].setFillColor(sf::Color::White);

    reset();

}

void playerMove(const float dt) {


    float direction = 0.f;
    if ((Keyboard::isKeyPressed(controls[0])) && (paddles[0].getPosition().y > 10 + (paddleSize.y / 2))) {
        direction--;
    }
    if ((Keyboard::isKeyPressed(controls[1])) && (paddles[0].getPosition().y < gameHeight - 10 - (paddleSize.y / 2))) {
        direction++;
    }
    paddles[0].move(0, direction * paddleSpeed * dt);


}

void ballMove(const float dt) {


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

        if (bx > gameWidth - ballRadius) {
            playerScore++;
        }

        if (bx < ballRadius) {
            AIScore++;
        }

        reset();

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

            if (bx < gameWidth / 2) {
                ballDirection = "right";
            } else {
                ballDirection = "left";
            }

        }


    }


}

void AIMove(const float dt) {

    if (ballDirection == "right") {

        float ai = 0.f;

        // if the ball is at least as far away as half the paddle size vertically

        if (
            (ball.getPosition().y - paddles[1].getPosition().y > paddleSize.y / 4) ||
            (ball.getPosition().y - paddles[1].getPosition().y < paddleSize.y / -4)
        ) {

            // follow ball and log direction

            if (ball.getPosition().y < paddles[1].getPosition().y) {
                ai--;
                ai_movement = "up";
            }
            if (ball.getPosition().y > paddles[1].getPosition().y) {
                ai++;
                ai_movement = "down";
            }
        } else {

            // continue in current direction

            if (ai_movement == "down") {
                ai++;
            } else if (ai_movement == "up") {
                ai--;
            }

        }

        if (
            (paddles[1].getPosition().y + ai > 10 + (paddleSize.y / 2)) &&
            (paddles[1].getPosition().y + ai < gameHeight - 10 - (paddleSize.y / 2))
        ) {
            paddles[1].move(0, ai * paddleSpeed * dt);
        }

    }


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

    playerMove(dt);
    ballMove(dt);
    AIMove(dt);

}

void render(RenderWindow &window) {

    window.draw(text);
    window.draw(yearText);
    window.draw(scoreText);
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);

}

int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(gameWidth,gameHeight), "SFML!");
    window.setVerticalSyncEnabled(true); // does this go here?
    load();


    // graphics card nearly dead, close automatically after a couple of seconds
    int x = 0;
    while (x < 1000) {
        x++;

        window.clear();
        update(window);
        render(window);
        window.display();

    }


    return 0;
}









