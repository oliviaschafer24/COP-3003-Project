#include <SFML/Graphics.hpp>
#include "Platforms.hpp"

platformClass::platformClass(int initialXPosition, int initialYPosition,
    sf::Sprite platformSprite){
    // Sets the platform to an initial position
    platformImage = platformSprite;
    platformImage.setPosition(initialXPosition, initialYPosition);
    // Find platform position
    platformTop = platformImage.getPosition().y;
    platformBottom = platformImage.getPosition().y + (platformImage.getLocalBounds().height);
    platformLeft = platformImage.getPosition().x;
    platformRight = platformImage.getPosition().x + (platformImage.getLocalBounds().width);
}

