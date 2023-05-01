#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Platforms.hpp"

using sf::Vector2f;

// Class for player movement
class playerClass {
    public:
        // Initialize variables
        float xPosition;
        float yPosition;
        float xVelocity;
        float yVelocity;
        bool isCollide;
        bool onGround;
        float accelGravity = -0.5f;
        float maxGravity = 3.0f;
        float speed = 2.0f;
        float jumpHeight = 2.0f;
        sf::Sprite playerImage;
        playerClass(sf::Sprite playerSprite);

        // Function to update movement
        void update(bool playerMoveUp, bool playerMoveDown, bool playerMoveLeft,
                    bool playerMoveRight, bool playerReset, platformClass platformArray[15], float gameTime);

        // Collision function
        void collide(float xVelocityDelta, float yVelocityDelta, platformClass platformArray[15]);
};

#endif // ENTITY_HPP_INCLUDED
