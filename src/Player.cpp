#include "Player.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
    animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    movement = Movement::idleLeft;
    body.setSize(sf::Vector2f(100.f, 150.f));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(0.f, 0.f);
    body.setTexture(texture);
}

Player::~Player() {

}

unsigned int Player::getRow() {
    return (unsigned int)(movement / 2);
}

bool Player::isAnimationReversed() {
    return (movement % 2);     // Default animation points to the right, and left facing modes are even.
}

void Player::Update(float deltaT) {
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    if (right && !left)
        movement = Movement::movingLeft;
    else if (left && !right)
        movement = Movement::movingRight;
    else if (movement == Movement::movingLeft)
        movement = Movement::idleLeft;
    else if (movement == Movement::movingRight)
        movement = Movement::idleRight;
    
    body.move((right*speed - left*speed)*deltaT, 0.f);
    animation.Update(getRow(), isAnimationReversed(), deltaT);

    body.setTextureRect(animation.uvRect);
}
void Player::Draw(sf::RenderWindow& window) {
    window.draw(body);
}