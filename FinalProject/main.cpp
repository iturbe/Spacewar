
/*
 Alonso Iturbe Sotomayor, Jonathan Ginsburg, Arthur Alves
 
 Final Project
 
 compile with: g++ *.cpp -o spacewar -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -std=c++11 -g
 
 run with: ./spacewar 
 
 */

#include "MovingSprite.hpp"

#include "MainFunctions.hpp"

// duh
int main(int, char const**) {
    // Create the main window
    sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(MAX_X, MAX_Y), "SPACEWAR 2020");
    sf::Music * music = new sf::Music();
    sf::Image * icon = new sf::Image();
	sf::Font * font = new sf::Font();
	sf::Text * scoreboard = new sf::Text();
    initialSetup(window, music, icon, font, scoreboard);
    
    // Set up alien
    MovingSprite * alien = new MovingSprite("invader.png", 0.2, "red_laser.png", 0.2, "Deez");
    
    // Set up player
    MovingSprite * spaceship = new MovingSprite("spaceship.png", 0.2, "blue_laser.png", 0.2, "Nuts");
	
	// Explosion when needed
	sf::Texture explosionTexture;
	explosionTexture.loadFromFile("otherExplosion.png");
	sf::Sprite * explosion = new sf::Sprite(explosionTexture);
	explosion->setScale(0.35, 0.35);
	
    // Load background
    sf::Texture texture;
    if (!texture.loadFromFile("spaceBG.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite background(texture);
    
    // alien
    alien->xcoord = 450;
    alien->ycoord = 50;
	alien->laserDirection = false;
    
    // spaceship
    spaceship->xcoord = 450;
    spaceship->ycoord = 600;
	spaceship->laserDirection = true;
	
	//main window loop
    while (window->isOpen())
    {
		// Check for relevant events
        sf::Event event;
        while (window->pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            
            // Escape pressed: exit
			if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, BUTTON_BACK)) { //not sure this works
                window->close();
            }
        }
        
        // check for player input
        checkArrowInput(spaceship);
		//checkWASDInput(alien);
		checkJoystickInput(alien);
        
        // move players accordingly
		alien->sprite->setPosition(alien->xcoord, alien->ycoord);
        spaceship->sprite->setPosition(spaceship->xcoord, spaceship->ycoord);
		
		
		
		
		
        // DRAW LOOP
        window->draw(background);
		
		// ALIEN
		drawPlayer(alien, spaceship, window, explosion);
		
		// PLAYER
		drawPlayer(spaceship, alien, window, explosion);
		
		// SCOREBOARD
		drawScoreboard(alien, spaceship, scoreboard, window);
        
        // DISPLAY
        window->display();
    }
    return EXIT_SUCCESS;
}
