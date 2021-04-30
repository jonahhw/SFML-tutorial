#include "Collider.h"
#include <cmath>

Collider::Collider(sf::RectangleShape& body):
    body(body)
{

}

Collider::~Collider() {

}

// push = 0 means that this object will be moved, while push = 1 means that the other will be moved
bool Collider::checkCollision(Collider other, float push) {
    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPosition = getPosition();
    sf::Vector2f thisHalfSize = getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    float intersectX = std::abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.f && intersectY < 0.f) {
        push = std::min(std::max(push, 0.f), 1.0f);

        if (intersectX > intersectY) {  // push it out on the x axis
            if (deltaX > 0.f) {
                move(intersectX*(1.f - push), 0.f);
                other.move(-intersectX * push, 0.f);
            } else {
                move(-intersectX*(1.f - push), 0.f);
                other.move(intersectX * push, 0.f);
            }
        } else {                        // push it out on the y
            if (deltaY > 0.f) {
                move(0.f, intersectX*(1.f - push));
                other.move(0.f, -intersectX * push);
            } else {
                move(0.f, -intersectX*(1.f - push));
                other.move(0.f, intersectX * push);
            }
        }
        return true;
    }
    return false;
}