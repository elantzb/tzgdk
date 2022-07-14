#pragma once
#include <map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

struct RGB 
{
	short r, g, b;
	RGB(short red, short green, short blue) : r(0), g(0), b(0)
	{
		r = red;
		g = green;
		b = blue;
	}
};

class TZGDK
{
private:
	TZGDK() {}
	TZGDK(TZGDK const&);
	void operator=(TZGDK const&);
	std::map<int, const char*>* musicMap;
	sf::Music* currentMusic;
	sf::RenderWindow* window;

public:
	static TZGDK& getInstance()
	{
		static TZGDK instance;
		return instance;
	}
	static void init();
	static void destroy();
	static void loadMusic(const char* path_to_file, int music_index);
	static bool playMusic(int music_index);
	static bool playMusic(int music_index, bool do_loop);
	static void stopMusic();

};
