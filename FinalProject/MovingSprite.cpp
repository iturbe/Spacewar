//
//  MovingSprite.cpp
//  5.SFML+Signals
//
//  Created by Alonso Iturbe on 3/16/17.
//  Copyright © 2017 Alonso Iturbe. All rights reserved.
//

#include "MovingSprite.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <string>

#define DEFAULT_COORD 100

class MovingSprite {
public:
    
    //variables
    sf::Sprite * sprite;
    sf::Texture texture;
    int xcoord;
    int ycoord;
    bool movingRight;
    
    //functions
    MovingSprite(std::string texturepath, float scale){
        sprite = new sf::Sprite(); // Instantiate sprite
        if (!texture.loadFromFile(texturepath)){ // load texture
            std::cout << "Could not load texture" << std::endl;
        }
        texture.setSmooth(true); //anti-aliasing
        sprite->setTexture(texture);
        sprite->setScale(scale, scale); //make smaller
        
        xcoord = DEFAULT_COORD;
        ycoord = DEFAULT_COORD;
        movingRight = true;
    }
};
