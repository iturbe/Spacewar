
/*
 Alonso Iturbe Sotomayor, Jonathan Ginsburg, Arthur Alves
 
 Final Project
 
 compile with: g++ main.cpp -o spacewar -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -std=c++11 -g
 
 run with: ./spacewar
 
 */

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <signal.h>
#include <unistd.h>

#include "MovingSprite.cpp"

#define BUTTON_A sf::Joystick::X // A button on controller
#define BUTTON_X sf::Joystick::Z // X button on controller
#define BUTTON_B sf::Joystick::Y // B button on controller
#define BUTTON_Y sf::Joystick::R // Y button on controller
#define BUTTON_LB sf::Joystick::U // Left bumper on controller
#define BUTTON_RB sf::Joystick::V // Right bumper on controller

#define AXIS_LEFT_X sf::Joystick::Axis::X //  Left stick x value
#define AXIS_LEFT_Y sf::Joystick::Axis::Y // Left stick y value

#define AXIS_RIGHT_X sf::Joystick::Axis::U // Right stick x value
#define AXIS_RIGHT_Y sf::Joystick::Axis::R // Right stick y value

#define TRIGGERS sf::Joystick::Axis::Z // Positive Z = LT, and Negative Z = RT

#define BUTTON_BACK sf::Joystick::PovX // Back button on controller
#define BUTTON_START sf::Joystick::PovY // Start button on controller

#define DPAD_X sf::Joystick::Axis::PovY // Dpad left and right
#define DPAD_Y sf::Joystick::Axis::PovX // Dpad Up and down

#define ALARM_TIMER 2
#define ALIEN_SPEED 5
#define PLAYER_SPEED 10

//TODO: SDFSDF

bool smallMovingRight = true;
bool paused = false;

//assign functionality to the alarm timer
void alarmFunc(int n){
    if (alarm(ALARM_TIMER) == 0) { //time is up
        smallMovingRight = !smallMovingRight; //switch direction
        alarm(ALARM_TIMER); // since timer is up, call once again for next time
    }
    signal(SIGALRM, alarmFunc); //reset handler
}

//override the ctrl-Z signal
void pauseFunc(int n){
    paused = true;
}

//override the ctrl-C signal
void playFunc(int n){
    paused = false;
}

// checks the WASD keys for player input
void checkInput(MovingSprite * sprite){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        sprite->ycoord -= PLAYER_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        sprite->ycoord += PLAYER_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        sprite->xcoord += PLAYER_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        sprite->xcoord -= PLAYER_SPEED;
    }
}

// checks the joystick (xbox 360 controller) for player input
void checkJoystickInput(MovingSprite * sprite){
    sf::Vector2f speed = sf::Vector2f(0.f,0.f);
    
    // note that the 0s are hardcoded and refer to the joystick #
    // if more than one joystick is connected to the same computer, this will have to become dynamic
    speed = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
    
    if (speed.x > 15.f || speed.x < -15.f || speed.y > 15.f || speed.y < -15.f){
        //square.move(turbo*speed.x*TimePerFrame.asSeconds(), turbo*speed.y*TimePerFrame.asSeconds());
        
        // multiply times .2 because otherwise the ∆ is huge
        sprite->ycoord = sprite->ycoord + speed.y * 0.20;
        sprite->xcoord = sprite->xcoord + speed.x * 0.20;
        
    }
    
}

// set up the window, music and icon
void initialSetup(sf::RenderWindow * window, sf::Music * music, sf::Image * icon){
    //set framerate limit
    window->setFramerateLimit(60);
    
    // Set the Icon
    if (!icon->loadFromFile("icon.png")) {
        return EXIT_FAILURE;
    }
    window->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());
    
    //music
    if (!music->openFromFile("8bitSpace.wav")) {
        return EXIT_FAILURE;
    }
    
    // Play music
    music->setLoop(true);
    music->play();
    
}

int main(int, char const**) {
    // Create the main window
    sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "SPACEWAR 2020");
    sf::Music * music = new sf::Music();
    sf::Image * icon = new sf::Image();
    initialSetup(window, music, icon);
    
    window->setFramerateLimit(60);
    
    // Set up alien
    MovingSprite * green = new MovingSprite("invader.png", 0.2);
    
    // Set up alien
    //MovingSprite * blue = new MovingSprite("blue.png", 0.5);
    
    // Set up player
    MovingSprite * player = new MovingSprite("spaceship.png", 0.2);
    
    // Load background
    sf::Texture texture;
    if (!texture.loadFromFile("spaceBG.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite background(texture);
    
    // green alien
    green->xcoord = 100;
    green->ycoord = 50;
    
    // spaceship
    player->xcoord = 450;
    player->ycoord = 750;
    
    /*
    // blue alien
    blue->xcoord = 100;
    blue->ycoord = 350;
    
    // SIGNALS
    sigset_t blocked_signals;
    sigset_t * blocked = nullptr; //create signal set
    blocked = &blocked_signals;
    sigfillset(blocked); //fill with all signals
    sigdelset(blocked, SIGALRM); //remove alarm signal from set
    sigdelset(blocked, SIGINT); //remove ctrl-c from set
    sigdelset(blocked, SIGTSTP); //remove ctrl-z from set
    
    //actually block the signals
    sigprocmask(SIG_SETMASK, blocked, NULL);
    
    // signal listeners
    signal(SIGTSTP, pauseFunc); // Z
    signal(SIGINT, playFunc); // C
    signal(SIGALRM, alarmFunc); // alarm
    alarm(ALARM_TIMER); //start alarm
     */
    
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
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, BUTTON_BACK)) {
                window->close();
            }
        }
        
        //check for user input
        checkInput(green);
        checkJoystickInput(player);
        
        //Move player and alien accordingly
        green->sprite->setPosition(green->xcoord, green->ycoord);
        player->sprite->setPosition(player->xcoord, player->ycoord);
        
        /*
        // blue alien movement (with alarm and pause)
        if (!paused) { //check to see if we can move, if not nothing executes at all
            if (smallMovingRight) { // this value changes every two seconds
                blue->xcoord += ALIEN_SPEED;
            } else {
                blue->xcoord -= ALIEN_SPEED;
            }
        }
        
        //move small alien accordingly
        blue->sprite->setPosition(blue->xcoord, blue->ycoord);
         */
        
        /*
        // Green alien movement
        if (green->movingRight) { //right
            if (green->xcoord < 800) {
                green->xcoord += ALIEN_SPEED;
            } else {
                green->xcoord -= ALIEN_SPEED;
                green->movingRight = false;
            }
        } else { //left
            if (green->xcoord > 50) { //still within bounds
                green->xcoord -= ALIEN_SPEED;
            } else {
                green->xcoord += ALIEN_SPEED;
                green->movingRight = true;
            }
        }
        
        //move alien accordingly
        green->sprite->setPosition(green->xcoord, green->ycoord);
         */
        
        // Draw loop (clear -> draw -> display)
        // CLEAR
        window->clear(sf::Color::White);
        
        // DRAW
        window->draw(background);
        //window->draw(text);
        window->draw(*green->sprite);
        //window->draw(*blue->sprite);
        window->draw(*player->sprite);
        
        // DISPLAY
        window->display();
        
    }
    
    return EXIT_SUCCESS;
}
