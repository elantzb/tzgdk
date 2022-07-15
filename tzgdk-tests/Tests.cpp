#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include "../tzgdk-lib/tzgdk-lib.h"

void TZGDK::GameLoop()
{
	static bool initialized = false;
	static bool keypressed = false;
	static float tileX = 0;

	if (!initialized)
	{
		//TZGDK::loadMusic("assets/sounds/stream/underground.flac", 1);
		//TZGDK::playMusic(1);

		TZGDK::setWindowSize(320, 320);
		TZGDK::setWindowTitle("TZGDK TEST");
		TZGDK::setWindowResolution(320, 320);
		TZGDK::setFramerateLimit(60);

		
		TZGDK::loadTexture("assets/images/spritesheets/map.bmp", 1);

		TZGDK::sprite(1, tileX, 0, 1);
		TZGDK::setSpriteTextureCoords(1, 64, 0, 32, 32);

		//std::cout << TZGDK::getSpriteWidth(1);

		initialized = true;
	}

	TZGDK::clearWindow(RGB(0, 0, 0));
	

	if (!keypressed && tzgdk::B() && tzgdk::V())
	{
		keypressed = true;
		//TZGDK::deleteSprite(1);
		//TZGDK::unloadTexture(1);
		TZGDK::setSpriteVisible(1, false);
	}
	else if(!keypressed)
		TZGDK::sprite(1, tileX++, 0, 1);

	/*if (getLastScanCode() >= 0)
	{
		std::cout << getLastScanCode() << std::endl;
	}*/
}

