#include "Player.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpImpulse):
    animation(texture, imageCount, switchTime), SpeedAddedX(speed), jumpImpulse(jumpImpulse),
    canJump(false), velocity(sf::Vector2f(0.f, 0.f))
{
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
    return !(movement % 2);     // Default animation points to the right, and left facing modes are even.
}

void Player::Update(float deltaT) {
    // Horizontal movement
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    velocity.x *= 0.1;
    if (left && !right) {
        movement = Movement::walkingLeft;
        velocity.x -= SpeedAddedX;
    }
    else if (right && !left) {
        movement = Movement::walkingRight;
        velocity.x += SpeedAddedX;
    } else if (movement > 1) {
        movement = (movement % 2) ? Movement::idleRight : Movement::idleLeft;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
        canJump = false;
        velocity.y -= jumpImpulse;
    }
    velocity.y += 1000.f * deltaT;   // gravity

    body.move(velocity * deltaT);
    
    animation.Update(getRow(), isAnimationReversed(), deltaT);

    body.setTextureRect(animation.uvRect);
}
void Player::Draw(sf::RenderWindow& window) {
    window.draw(body);
}

void Player::onCollision(sf::Vector2f direction) {
    if (direction.y < 0.0f) {
        canJump = true;
    }
}