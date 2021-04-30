#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 512.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(512, 512), "Walking penguin", sf::Style::Default);
    sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));


    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/penguin.png");
    
    Player player(&playerTexture, sf::Vector2u(3, 9), 0.25f, 200.f);

    Platform platform1(nullptr, sf::Vector2f(100.f, 200.f), sf::Vector2f(-200.f, 0.f));
    Platform platform2(nullptr, sf::Vector2f(100.f, 200.f), sf::Vector2f(200.f, 0.f));
    
    float deltaT = 0.f;
    sf::Clock clock;

    bool inFocus = true;

    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case::sf::Event::Resized:
                    view.setSize(evnt.size.width, evnt.size.height);
                    break;
                case sf::Event::TextEntered:
                    // if (evnt.text.unicode < 128)
                    //     printf("%c", evnt.text.unicode);
                    //     fflush(stdout);
                    break;
                case sf::Event::LostFocus:
                    inFocus = false;
                    break;
                case sf::Event::GainedFocus:
                    inFocus = true;
                    break;
                default:
                    break;
            }
        }

        deltaT = clock.restart().asSeconds();

        if (inFocus)
            player.Update(deltaT);

        platform1.getCollider().checkCollision(player.getCollider(), 0.f);
        platform2.getCollider().checkCollision(player.getCollider(), 1.f);
        
        view.setCenter(player.getPosition());

        window.clear(sf::Color(150, 150, 150, 255));
        window.setView(view);

        player.Draw(window);
        platform1.Draw(window);
        platform2.Draw(window);

        window.display();
    }
    return 0;
}
