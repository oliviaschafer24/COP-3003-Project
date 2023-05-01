#ifndef PLATFORMS_HPP_INCLUDED
#define PLATFORMS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Platforms.hpp"

// Class for platforms
class platformClass {
    public:
        // Initialize variables
        float xPosition;
        float yPosition;
        float xVelocity;
        float yVelocity;
        float platformTop;
        float platformBottom;
        float platformLeft;
        float platformRight;
        sf::Sprite platformImage;
        platformClass(int initialXPosition, int initialYPosition,
                      sf::Sprite platformSprite);
};

#endif // PLATFORMS_HPP_INCLUDED
