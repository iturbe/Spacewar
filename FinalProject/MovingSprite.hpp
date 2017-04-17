//
//  MovingSprite.hpp
//  5.SFML+Signals
//
//  Created by Alonso Iturbe on 3/16/17.
//  Copyright © 2017 Alonso Iturbe. All rights reserved.
//

#ifndef MovingSprite_hpp
#define MovingSprite_hpp

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class MovingSprite {
public:
	
	std::string playerName;
	
	//variables
	sf::Sprite * sprite;
	sf::Texture texture;
	int xcoord;
	int ycoord;
	
	sf::Sprite * laser;
	sf::Texture laserTexture;
	bool laserActive;
	int laserX;
	int laserY;
	bool laserDirection; //1 for up, 0 for down
	
	int hits;
	int points;
	
	//bool movingRight;
	
	//functions
	MovingSprite(std::string texturepath, float scale, std::string laserpath, float laserscale, std::string name);
	
	void shoot(int current_xcoord, int current_ycoord);
};


#endif /* MovingSprite_hpp */
