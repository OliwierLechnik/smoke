#include <SFML/Graphics.hpp>
#include <iostream>

#include "smoke.cpp"
#include "sprayer.cpp"

int main () {
    using std::cout;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1200,800), "title", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    

    Sprayer sprayer({360,400}, 90);
    sf::Mouse mouse;

    sf::Clock clock;
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time dTime = clock.restart();
        sf::Vector2i mPos = mouse.getPosition(window);

        float angle = atan2(mPos.x-360,400-mPos.y);

        if(mouse.isButtonPressed(sf::Mouse::Left)) {
            
        }

        sprayer.update(dTime.asSeconds(),0,0,angle*RAD_TO_DEG);

        window.clear();
        window.draw(sprayer);
        window.display();
    }

    return 0;
}