#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include <vector>

const static int INITIAL_SCREEN_X = 512.f;
const static int INITIAL_SCREEN_Y = 512.f;

int main() {
    sf::RenderWindow window(sf::VideoMode(INITIAL_SCREEN_X, INITIAL_SCREEN_Y), "Walking penguin", sf::Style::Default);
    sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(INITIAL_SCREEN_X, INITIAL_SCREEN_Y));


    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/penguin.png");
    
    Player player(&playerTexture, sf::Vector2u(3, 9), 0.25f, 200.f, 1000.f);

    std::vector<Platform> platforms;
    platforms.push_back(Platform(nullptr, sf::Vector2f(100.f, 200.f), sf::Vector2f(-100.f, 0.f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(100.f, 200.f), sf::Vector2f(200.f, 0.f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(1000.f, 100.f), sf::Vector2f(0.f, 150.f)));
    
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

        for (int i = 0; i < platforms.size(); i++) {        // Stupid hack to make it possible to move some blocks
            sf::Vector2f direction;
            if (platforms[i].getCollider().checkCollision(player.getCollider(), direction, (i % 2) ? 0.f : 1.f)) {
                player.onCollision(direction);
            }
        }
        
        view.setCenter(player.getPosition());

        window.clear(sf::Color(150, 150, 150, 255));
        window.setView(view);

        player.Draw(window);
        // std::printf("Drawing player at (%f, %f)\n", player.getPosition().x, player.getPosition().y);
        for (Platform& platform : platforms) {
            platform.draw(window);
            // std::printf("Drawing platform at (%f, %f)\n", platform.getCollider().getPosition().x, platform.getCollider().getPosition().y);
        }
        
        window.display();
    }
    return 0;
}
