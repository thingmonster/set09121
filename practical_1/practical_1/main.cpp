#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;





void load() {

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

}

int main()
{

    // create window, set vsync, set up game
    sf::RenderWindow window(sf::VideoMode(500,500), "SFML!");
    window.setVerticalSyncEnabled(true); // does this go here?
    load();

    // test
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(200, 150, 100));


    // graphics card nearly dead, close automatically after a couple of seconds
    int x = 0;
    while (x < 10) {

        x++;

        // move game forwards
        window.clear();
        update(window);
        render(window);

        // test
        window.draw(shape);

        window.display();

    }


    return 0;
}
