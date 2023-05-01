// Olivia Schafer
// COP 3003 | Programming II
// Final (for the purposes of this project) version of the platformer

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"
#include "Platforms.hpp"

using sf::Keyboard;
using sf::Vector2f;

// Screen size (1920 x 1080)
int windowWidth = 1920;
int windowHeight = 1080;

int main() {
    // Creates the main window
    sf::RenderWindow app(sf::VideoMode(windowWidth, windowHeight), "Final Project Platformer");

    // View for camera movements
    sf::View view(Vector2f(0.0f, 0.0f), Vector2f(windowWidth, windowHeight));

    // Sets gameClock
    sf::Clock gameClock;

    // Sets movements to false until a key is pressed
    bool playerMoveUp, playerMoveDown, playerMoveLeft, playerMoveRight, playerReset = false;

    // Loads the block texture and makes it a sprite to display
    sf::Texture whiteBlockTexture;
    whiteBlockTexture.loadFromFile("whiteBlock.PNG");
    sf::Sprite whiteBlockSprite(whiteBlockTexture);
    whiteBlockSprite.setTextureRect(sf::IntRect(0,0,80,80));

    // Loads the platform texture and makes it a sprite to display
    sf::Texture floorTempTexture;
    floorTempTexture.loadFromFile("floorTemp.PNG");
    sf::Sprite floorTempSprite(floorTempTexture);
    floorTempSprite.setTextureRect(sf::IntRect(0,0,400,15));

    // Instances class
    playerClass playerObject(whiteBlockSprite);

    // Array for platforms
    platformClass platformArray[15] = {platformClass(-160, 180, floorTempSprite),
                                      platformClass(500, 180, floorTempSprite),
                                      platformClass(1100, 180, floorTempSprite),
                                      platformClass(1900, 180, floorTempSprite),
                                      platformClass(2700, 180, floorTempSprite),
                                      platformClass(3500, -200, floorTempSprite),
                                      platformClass(4500, -500, floorTempSprite),
                                      platformClass(3000, -700, floorTempSprite),
                                      platformClass(2000, -750, floorTempSprite),
                                      platformClass(1000, -900, floorTempSprite),
                                      platformClass(-500, -1000, floorTempSprite),
                                      platformClass(-1700, -1100, floorTempSprite),
                                      platformClass(-2500, -1300, floorTempSprite),
                                      platformClass(-900, -1500, floorTempSprite),
                                      platformClass(-160, -1800, floorTempSprite) };

	// Starts the game loop
    while (app.isOpen()) {
        // Processes events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Closes window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Assigns keys for movement
        if(Keyboard::isKeyPressed(Keyboard::W)) {
            playerMoveUp = true; }
        else {
            playerMoveUp = false; }

        if(Keyboard::isKeyPressed(Keyboard::S)) {
            playerMoveDown = true; }
        else {
            playerMoveDown = false; }

        if(Keyboard::isKeyPressed(Keyboard::A)) {
            playerMoveLeft = true; }
        else {
            playerMoveLeft = false; }

        if(Keyboard::isKeyPressed(Keyboard::D)) {
            playerMoveRight = true; }
        else {
            playerMoveRight = false; }
        if(Keyboard::isKeyPressed(Keyboard::R)) {
            playerReset = true; }
        else {
            playerReset = false; }

        float gameTime = gameClock.getElapsedTime().asSeconds();

        // Updates movement
        playerObject.update(playerMoveUp, playerMoveDown, playerMoveLeft,
                            playerMoveRight, playerReset, platformArray, gameTime);

        // Restarts gameClock
        gameClock.restart().asSeconds();

        // Sets center for camera movement based on where the player's position is
        view.setCenter(Vector2f(playerObject.playerImage.getPosition().x +
                       playerObject.playerImage.getLocalBounds().width / 2.0f,
                       playerObject.playerImage.getPosition().y +
                       playerObject.playerImage.getLocalBounds().height / 2.0f));

        // Set background color
        app.clear(sf::Color(26, 26, 26));

        // Set view for the camera
        app.setView(view);

        // Imports Arial font and sets up text used
        sf::Font arialFont;
        arialFont.loadFromFile("arial.ttf");

        sf::Text messageOne("Follow the platforms using W,A,S,D", arialFont, 25);
        messageOne.setOrigin(160,30);

        sf::Text messageTwo("If you fall, press R to reset", arialFont, 15);
        messageTwo.setOrigin(60,5);

        sf::Text messageThree("You win!", arialFont, 25);
        messageThree.setOrigin(10, 1930);

        // Draws text and block sprite
        app.draw(playerObject.playerImage);
        app.draw(messageOne);
        app.draw(messageTwo);
        app.draw(messageThree);

        // Lets the block sprite be moved when keys are pressed and changes velocity
        playerObject.playerImage.move(Vector2f(playerObject.xVelocity, playerObject.yVelocity));

        // Draws the platform sprites in the array
        for(int i = 0; i < 15; i++){
            app.draw(platformArray[i].platformImage);
        }

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
