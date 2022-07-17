#include <iostream>
#include "../tzgdk-lib/tzgdk-lib.h"

void tzgdk::GameLoop()
{
	static bool initialized = false;
	static bool keypressed = false;
	static float tileX = 48, tileY = 48;
	static int spriteFrame = 0;
	static int frameTimer = tzgdk::getMilliTime();
	static int startTime;

	if (!initialized)
	{
		//tzgdk::loadMusic("assets/sounds/stream/underground.flac", 1);
		//tzgdk::loadMusic("assets/sounds/stream/simplertimes.flac", 2);
		//tzgdk::playMusic(1);
		//tzgdk::playMusic(2, true);

		tzgdk::setWindowSize(320, 320);
		tzgdk::setWindowTitle("TZGDK TEST");
		tzgdk::setWindowResolution(320, 320);
		tzgdk::setFramerateLimit(60);

		
		tzgdk::loadTexture("assets/images/spritesheets/map.bmp", 1);

		tzgdk::sprite(1, 48, 48, 1);
		tzgdk::setSpriteTextureCoords(1, 64, 0, 32, 32);
		tzgdk::sprite(2, 32, 32, 1);
		//tzgdk::setSpriteTextureCoords(2, 96, 0, 32, 32);
		tzgdk::setSpriteTextureCoordsNormalized(2, 0.0f, 0.4f, 0.1f, 0.1f, 1);

		tzgdk::setSpritePriority(2, 1);
		//tzgdk::setSpriteScale(1, 0.5f, 0.5f);

		startTime = tzgdk::getMilliTime();

		tzgdk::createAnimatedSprite(3, "assets/images/spritesheets/sprite1.bmp", 4, 2, 3);


		initialized = true;
	}

	tzgdk::clearWindow(RGB(0, 0, 0));


	//tileX += tileDX;
	/*tzgdk::sprite(1, tileX, tileY, 1);

	if (tzgdk::sc::Up())
		tileY--;
	if (tzgdk::sc::Right())
		tileX++;
	if (tzgdk::sc::Down())
		tileY++;
	if (tzgdk::sc::Left())
		tileX--;
	
	if (tzgdk::testSpriteOverlap(1, 2))
	{
		std::cout << "overlap!" << std::endl;
	}
	else
	{
		std::cout << std::endl;
	}*/

	
	
	tzgdk::sprite(3, 128, 128, 3);

	if (tzgdk::getMilliTime() - frameTimer > 400)
	{
		frameTimer = tzgdk::getMilliTime();
		spriteFrame ^= 1;
		tzgdk::setSpriteFrame(3, spriteFrame, 3);
	}

	//if (!keypressed && tzgdk::sc::B() && tzgdk::sc::V())
	/*if (tzgdk::getMilliTime() - startTime > 2000)
	{
		//keypressed = true;
		//tzgdk::deleteSprite(1);
		//tzgdk::unloadTexture(1);
		tzgdk::setSpriteVisible(1, false);
	}
	else //if(!keypressed)
		tzgdk::sprite(1, tileX++, 0, 1);*/

	

}

