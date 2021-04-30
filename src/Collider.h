#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Collider {
    public:
        Collider(sf::RectangleShape& body);
        ~Collider();

        void move(float dx, float dy) { body.move(dx, dy); }

        bool checkCollision(Collider other, float push);       // explained above definition
        sf::Vector2f getPosition() { return body.getPosition(); }
        sf::Vector2f getHalfSize() { return body.getSize() / 2.f; }

    private:
        sf::RectangleShape& body;
    
};