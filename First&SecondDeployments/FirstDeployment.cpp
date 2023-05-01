// Olivia Schafer
// COP 3003 | Programming II
// The beginning of a platformer for the assigned project, using a white block
// as a placeholder for the player and a platform to go onto

#include <SFML/Graphics.hpp>
#include <iostream>

// Screen size (1290 x 720)
int windowWidth = 1280;
int windowHeight = 720;

using sf::Keyboard;
using sf::Vector2f;

// Class for platforms [TODO]
class platformClass{
    public:
        float xPosition;
        float yPosition;
        float xVelocity;
        float yVelocity;
        platformClass(float xPosition, float yPosition){
            xPosition = xPosition;
            yPosition = yPosition;
        }

};

// Class for player movement
class playerClass{
    public:
        float xPosition;
        float yPosition;
        float xVelocity;
        float yVelocity;
        playerClass(){
            xPosition = 0;
            yPosition = 0;
            xVelocity = 0;
            yVelocity = 0;
        }
        // Function to update movement
        void update(bool playerMoveUp, bool playerMoveDown, bool playerMoveLeft, bool playerMoveRight){
            // Player movement speeds for all directions
            if(playerMoveRight){
                xVelocity = 0.2;
            }
            if(playerMoveLeft){
                xVelocity = -0.2;
            }
            if(playerMoveDown){
                yVelocity = 0.2;
            }
            if(playerMoveUp){
                yVelocity = -0.2;
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


            // Prevents the player from leaving the screen
            if(yPosition > 320 || yPosition < -320){
                yVelocity = 0;
            }

            if(xPosition > 600 || xPosition < -600){
                xVelocity = 0;
            }

            // Collision for the platform [TO BE POLISHED]
            if(yPosition > 200 && xPosition > 200){
                yVelocity = 0;
            }
        }
};


int main() {
    // Creates the main window
    sf::RenderWindow app(sf::VideoMode(windowWidth, windowHeight), "WIP Platformer");

    bool playerMoveUp, playerMoveDown, playerMoveLeft, playerMoveRight = false;

    playerClass playerObject;

    // Loads the block texture and makes it a sprite to display
    sf::Texture whiteBlockTexture;
    whiteBlockTexture.loadFromFile("whiteBlock.PNG");
    sf::Sprite whiteBlockSprite(whiteBlockTexture);
    whiteBlockSprite.setOrigin(-600, -320);

    // Loads the platform texture and makes it a sprite to display
    sf::Texture floorTempTexture;
    floorTempTexture.loadFromFile("floorTemp.PNG");
    sf::Sprite floorTempSprite(floorTempTexture);
    floorTempSprite.setOrigin(-900, -600);


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

        // Updates movement
        playerObject.update(playerMoveUp, playerMoveDown, playerMoveLeft, playerMoveRight);

        // Clears screen
        app.clear();

        // Draws block and platform sprites
        app.draw(whiteBlockSprite);
        app.draw(floorTempSprite);

        // Lets the block sprite be moved when keys are pressed and changes velocity
        whiteBlockSprite.move(Vector2f(playerObject.xVelocity, playerObject.yVelocity));

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
