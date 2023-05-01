#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"
#include "Platforms.hpp"

playerClass::playerClass(sf::Sprite playerSprite){
    playerImage = playerSprite;
    xPosition = 0;
    yPosition = 0;
    xVelocity = 0;
    yVelocity = 0;
    isCollide = false;
}

// Function to update movement
void playerClass::update(bool playerMoveUp, bool playerMoveDown, bool playerMoveLeft,
    bool playerMoveRight, bool playerReset, platformClass platformArray[15], float gameTime){
    // Player movement speeds for all directions
    if(playerMoveRight){
        xVelocity = 1;
    }
    if(playerMoveLeft){
        xVelocity = -1;
    }
    if(playerMoveDown){
        yVelocity = 1;
    }
    if(playerMoveUp && onGround){
        yVelocity = jumpHeight * -1;
    }

    // Sets player velocity to zero if they are not pressing a key
    if(!(playerMoveRight || playerMoveLeft)){
        xVelocity = 0;
    }
    if(!(playerMoveUp || playerMoveDown)){
        yVelocity = 1;
    }

    // Finds position by adding velocity (from movement)
    xPosition += xVelocity;
    yPosition += yVelocity;

    xVelocity *= 0.99f;
    yVelocity *= 0.99f;

    // Collision function call with movement (velocity)
    playerImage.move(sf::Vector2f(xVelocity, 0));
    collide(xVelocity, 0, platformArray);

    onGround = false;
    playerImage.move(sf::Vector2f(0, yVelocity));
    collide(0, yVelocity, platformArray);

    // Sets reset button
    if(playerReset){
        playerImage.setPosition(0,0);
    }
}

// Collision function
void playerClass::collide(float xVelocityDelta, float yVelocityDelta, platformClass platformArray[15]){
    // For each platform
    for(int i = 0; i < 15; i++) {
        // If the player has the same position as the position of the platform
        if(playerImage.getPosition().x + playerImage.getLocalBounds().width > platformArray[i].platformLeft &&
            playerImage.getPosition().x < platformArray[i].platformRight &&
            playerImage.getPosition().y + playerImage.getLocalBounds().height > platformArray[i].platformTop &&
            playerImage.getPosition().y < platformArray[i].platformBottom){
            isCollide = true;
        } else {
            isCollide = false;
        }
        // If the collision occurs
        if(isCollide){
            // Sets player position to the position they are in (so they cant move)
            if(xVelocityDelta > 0){
                playerImage.setPosition(Vector2f(platformArray[i].platformLeft -
                playerImage.getLocalBounds().width-1, playerImage.getPosition().y));
            } if(xVelocityDelta < 0){
                playerImage.setPosition(Vector2f(platformArray[i].platformRight+1,
                playerImage.getPosition().y));
            } if(yVelocityDelta > 0){
                playerImage.setPosition(Vector2f(playerImage.getPosition().x,
                platformArray[i].platformTop - playerImage.getLocalBounds().height-1));
                onGround = true;
            } if(yVelocityDelta < 0){
                playerImage.setPosition(Vector2f(playerImage.getPosition().x,
                platformArray[i].platformBottom+1));
            }
        }
    }
}
