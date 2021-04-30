#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
    body.setSize(size);
    body.setPosition(position);
    body.setTexture(texture);
    body.setOrigin(body.getSize() / 2.f);
}

Platform::~Platform() {

}
