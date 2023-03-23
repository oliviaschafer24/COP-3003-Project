// Olivia Schafer
// COP 3003 | Programming II
// Continuation of the platformer, adding code for camera movement
// and collision/platform arrays (need to fix)

#include <SFML/Graphics.hpp>
#include <iostream>

// Screen size (1280 x 720)
int windowWidth = 1280;
int windowHeight = 720;

using sf::Keyboard;
using sf::Vector2f;

// Class for platforms
class platformClass{
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
        int scale;
        sf::Sprite platformImage;
        platformClass(int initialXPosition, int initialYPosition,
                      sf::Sprite platformSprite){
            scale = 1;
            // Sets the platform to an initial position
            platformImage = platformSprite;
            platformImage.setPosition(initialXPosition, initialYPosition);
            // Find platform position
            platformTop = platformImage.getPosition().y;
            platformBottom = platformImage.getPosition().y +
                            (platformImage.getLocalBounds().height * scale);
            platformLeft = platformImage.getPosition().x;
            platformRight = platformImage.getPosition().x +
                            (platformImage.getLocalBounds().width * scale);

        }
};

// Class for player movement
class playerClass{
    public:
        // Initialize variables
        float xPosition;
        float yPosition;
        float xVelocity;
        float yVelocity;
        bool isCollide;
        int scale;
        sf::Sprite playerImage;
        playerClass(sf::Sprite playerSprite){
            playerImage = playerSprite;
            xPosition = 0;
            yPosition = 0;
            xVelocity = 0;
            yVelocity = 0;
            scale = 1;
            isCollide = false;
        }
        // Function to update movement
        void update(bool playerMoveUp, bool playerMoveDown, bool playerMoveLeft,
                    bool playerMoveRight, platformClass platformArray[2], float gameTime){
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
            if(playerMoveUp){
                yVelocity = -1;
            }

            // Sets player velocity to zero if they are not pressing a key
            if(!(playerMoveRight || playerMoveLeft)){
                xVelocity = 0;
            }
            if(!(playerMoveUp || playerMoveDown)){
                yVelocity = 0;
            }


            // Finds position by adding velocity (from movement)
            xPosition += xVelocity;
            yPosition += yVelocity;

            xVelocity = 0.99f * xVelocity;
            yVelocity = 0.99f * yVelocity;


            // Collision function call with movement (velocity)
            playerImage.move(sf::Vector2f(xVelocity * gameTime, 0));
            collide(xVelocity, 0, platformArray);
            playerImage.move(sf::Vector2f(0, yVelocity * gameTime));
            collide(0, yVelocity, platformArray);
        }
        // Collision function
        void collide(float xVelocityDelta, float yVelocityDelta, platformClass platformArray[2]){
            // For each platform
            for(int i = 0; i < 2; i++) {
                // If the player has the same position as the position of the platform
                if(playerImage.getPosition().x + playerImage.getLocalBounds().width
                   * scale > platformArray[i].platformLeft
                   && playerImage.getPosition().x < platformArray[i].platformRight
                   && playerImage.getPosition().y + playerImage.getLocalBounds().height
                   * scale > platformArray[i].platformTop
                   && playerImage.getPosition().y < platformArray[i].platformBottom){
                    isCollide = true;
                } else {
                    isCollide = false;
                }
                // If the collision occurs
                if(isCollide){
                    // Sets player position to the position they are in (so they cant move)
                    if(xVelocityDelta > 0){
                        playerImage.setPosition(Vector2f(platformArray[i].platformLeft -
                        playerImage.getLocalBounds().width * scale, playerImage.getPosition().y));
                    } if(xVelocityDelta < 0){
                        playerImage.setPosition(Vector2f(platformArray[i].platformRight,
                        playerImage.getPosition().y));
                    } if(yVelocityDelta > 0){
                        playerImage.setPosition(Vector2f(playerImage.getPosition().x,
                        platformArray[i].platformTop - playerImage.getLocalBounds().height * scale));
                    } if(yVelocityDelta < 0){
                        playerImage.setPosition(Vector2f(playerImage.getPosition().x,
                        platformArray[i].platformBottom));
                    }
                }
            }
        }

};


int main() {
    // Creates the main window
    sf::RenderWindow app(sf::VideoMode(windowWidth, windowHeight), "WIP Platformer");

    // View for camera movements
    sf::View view(Vector2f(0.0f, 0.0f), Vector2f(windowWidth, windowHeight));

    // Sets gameClock
    sf::Clock gameClock;

    bool playerMoveUp, playerMoveDown, playerMoveLeft, playerMoveRight = false;

    // Loads the block texture and makes it a sprite to display
    sf::Texture whiteBlockTexture;
    whiteBlockTexture.loadFromFile("whiteBlock.PNG");
    sf::Sprite whiteBlockSprite(whiteBlockTexture);
    whiteBlockSprite.setOrigin(0, -100);

    // Loads the platform texture and makes it a sprite to display
    sf::Texture floorTempTexture;
    floorTempTexture.loadFromFile("floorTemp.PNG");
    sf::Sprite floorTempSprite(floorTempTexture);
    // floorTempSprite.setTextureRect(sf::IntRect(0,0,15,15));
    floorTempSprite.setOrigin(265, -300);

    // Instances classes
    playerClass playerObject(whiteBlockSprite);
    platformClass platformObject(0, 0, floorTempSprite);

    // Array for platforms
    platformClass platformArray[2] = {platformClass(265, -300, floorTempSprite),
                                      platformClass(365, -200, floorTempSprite) };


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

        float gameTime = gameClock.getElapsedTime().asSeconds();

        // Updates movement
        playerObject.update(playerMoveUp, playerMoveDown, playerMoveLeft,
                            playerMoveRight, platformArray, gameTime);

        // Restarts gameClock
        gameClock.restart().asSeconds();

        // Sets center for camera movement based on where the player's position is
        view.setCenter(Vector2f(playerObject.playerImage.getPosition().x +
                       playerObject.playerImage.getLocalBounds().width * playerObject.scale / 2.0f,
                       playerObject.playerImage.getPosition().y +
                       playerObject.playerImage.getLocalBounds().height * playerObject.scale / 2.0f));

        // Set background color
        app.clear(sf::Color(26, 26, 26));

        // Set view for the camera
        app.setView(view);

        // Imports Arial font and displays level text
        sf::Font arialFont;
        arialFont.loadFromFile("arial.ttf");
        sf::Text levelOne("Level 1", arialFont, 20);
        app.draw(levelOne);

        // Draws block and platform sprites
        app.draw(playerObject.playerImage);
        app.draw(platformObject.platformImage);

        // Lets the block sprite be moved when keys are pressed and changes velocity
        playerObject.playerImage.move(Vector2f(playerObject.xVelocity, playerObject.yVelocity));

        // Draws the platforms in the array
        for(int i = 0; i < 2; i++){
            app.draw(platformArray[2].platformImage);
        }

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}

