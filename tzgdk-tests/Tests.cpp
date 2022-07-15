#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include "../tzgdk-lib/tzgdk-lib.h"

void tzgdk::GameLoop()
{
	static bool initialized = false;
	static bool keypressed = false;
	static float tileX = 0;

	if (!initialized)
	{
		//tzgdk::loadMusic("assets/sounds/stream/underground.flac", 1);
		//tzgdk::playMusic(1);

		tzgdk::setWindowSize(320, 320);
		tzgdk::setWindowTitle("TZGDK TEST");
		tzgdk::setWindowResolution(320, 320);
		tzgdk::setFramerateLimit(60);

		
		tzgdk::loadTexture("assets/images/spritesheets/map.bmp", 1);

		tzgdk::sprite(1, tileX, 0, 1);
		tzgdk::setSpriteTextureCoords(1, 64, 0, 32, 32);

		//std::cout << tzgdk::getSpriteWidth(1);

		initialized = true;
	}

	tzgdk::clearWindow(RGB(0, 0, 0));
	

	if (!keypressed && tzgdk::sc::B() && tzgdk::sc::V())
	{
		keypressed = true;
		//tzgdk::deleteSprite(1);
		//tzgdk::unloadTexture(1);
		tzgdk::setSpriteVisible(1, false);
	}
	else if(!keypressed)
		tzgdk::sprite(1, tileX++, 0, 1);

	/*if (getLastScanCode() >= 0)
	{
		std::cout << getLastScanCode() << std::endl;
	}*/
}

