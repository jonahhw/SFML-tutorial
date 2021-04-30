
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Collider.h"

class Platform {
    public:
        Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
        ~Platform();

        void Draw(sf::RenderWindow& window) { window.draw(body); }
        Collider getCollider() { return Collider(body); }
    
    private:
        sf::RectangleShape body;
};