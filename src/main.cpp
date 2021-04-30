#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdio>
#include <iostream>
#include "Player.h"

static const float VIEW_HEIGHT = 512.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(512, 512), "Walking penguin", sf::Style::Default);
    sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));


    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/penguin.png");
    
    Player player(&playerTexture, sf::Vector2u(3, 9), 0.25f, 100.f);
    
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
        
        view.setCenter(player.getPosition());

        window.clear(sf::Color(150, 150, 150, 255));
        window.setView(view);

        player.Draw(window);

        window.display();
    }
    return 0;
}
