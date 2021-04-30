#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include "Animation.h"

class Player {
    public:
        Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
        ~Player();

        void Update(float deltaT);
        void Draw(sf::RenderWindow& window);

        sf::Vector2f getPosition() { return body.getPosition(); }

    private:
        unsigned int getRow();
        bool isAnimationReversed();

    private:
        sf::RectangleShape body;
        Animation animation;
        enum Movement{      // Left facing is even; numbers correnpond to row * 2
            idleLeft=0,
            idleRight,
            movingLeft,
            movingRight
        };
        Movement movement;
        float speed;
        sf::Texture texture;
};