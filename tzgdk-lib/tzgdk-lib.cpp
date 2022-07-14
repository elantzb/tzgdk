// tzgdk-lib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "tzgdk-lib.h"



void TZGDK::init()
{
	TZGDK::getInstance().musicMap = new std::map<int, const char*>;
	TZGDK::getInstance().currentMusic = new sf::Music;
	TZGDK::getInstance().window = new sf::RenderWindow;
}

void TZGDK::destroy()
{
	TZGDK::getInstance().musicMap->clear();
	delete TZGDK::getInstance().musicMap;
	delete TZGDK::getInstance().currentMusic;
}

void TZGDK::loadMusic(const char* path_to_file, int music_index)
{
	(*(TZGDK::getInstance().musicMap)).insert_or_assign(music_index, path_to_file);
}

bool TZGDK::playMusic(int music_index)
{
	const char* musicPath = (*(TZGDK::getInstance().musicMap)).at(music_index);
	if (!(*(TZGDK::getInstance().currentMusic)).openFromFile(musicPath))
		return false;

	(*(TZGDK::getInstance().currentMusic)).play();

	return true;
}

bool TZGDK::playMusic(int music_index, bool do_loop)
{
	const char* musicPath = (*(TZGDK::getInstance().musicMap)).at(music_index);
	if (!(*(TZGDK::getInstance().currentMusic)).openFromFile(musicPath))
		return false;

	(*(TZGDK::getInstance().currentMusic)).setLoop(true);
	(*(TZGDK::getInstance().currentMusic)).play();

	return true;
}

void TZGDK::stopMusic()
{
	(*(TZGDK::getInstance().currentMusic)).stop();
}