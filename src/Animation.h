#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Animation {
    public:
        Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
        ~Animation();

        void Update(int row, bool reverseDirection, float deltaT);

    public:
        sf::IntRect uvRect;

    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float totalTime;
        float switchTime;
        
};