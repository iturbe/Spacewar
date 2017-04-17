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

MovingSprite::MovingSprite(std::string texturepath, float scale, std::string laserpath, float laserscale, std::string name){
	
	//sprite
	sprite = new sf::Sprite(); // Instantiate
	if (!texture.loadFromFile(texturepath)){ // load texture
		std::cout << "Could not load sprite texture" << std::endl;
	}
	texture.setSmooth(true); //anti-aliasing
	sprite->setTexture(texture);
	sprite->setScale(scale, scale); //make smaller
	
	xcoord = DEFAULT_COORD;
	ycoord = DEFAULT_COORD;
	
	// laser beam
	laser = new sf::Sprite(); // Instantiate
	if (!laserTexture.loadFromFile(laserpath)){ // load texture
		std::cout << "Could not load laser texture" << std::endl;
	}
	laserTexture.setSmooth(true); //anti-aliasing
	laser->setTexture(laserTexture);
	laser->setScale(laserscale, laserscale); //make smaller
	laserActive = false;
	
	hits = 0;
	points = 0;
	
	playerName = name;
}

void MovingSprite::shoot(int current_xcoord, int current_ycoord){
	laserX = current_xcoord;
	laserY = current_ycoord;
	laserActive = true;
}
