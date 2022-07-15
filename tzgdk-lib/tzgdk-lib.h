#pragma once
#include <map>
//#include <thread>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

struct RGB 
{
	int r, g, b;
	RGB(int red, int green, int blue) : r(0), g(0), b(0)
	{
		r = red;
		g = green;
		b = blue;
	}
};

struct SpriteWrapper
{
	sf::Sprite* sprite;
	bool isVisible;
	int order; /// TODO: Look into reordering sprite draws.
	SpriteWrapper(sf::Sprite* p_sprite)
	{
		sprite = p_sprite;
		isVisible = true;
		order = 0;
	}
};

class TZGDK
{
private:
	TZGDK() {}
	TZGDK(TZGDK const&);
	void operator=(TZGDK const&) {};

	std::map<int, const char*>* musicMap;
	sf::Music* currentMusic;

	sf::RenderWindow* window;

	/// TODO: Investigate multi-threading for drawing
	//std::thread* drawThread;

	std::map<int, sf::Image*>* loadedImages;
	std::map<int, sf::Texture*>* loadedTextures;
	std::map<int, SpriteWrapper>* loadedSprites;

public:
	static TZGDK& getInstance()
	{
		static TZGDK instance;
		return instance;
	}
	static void init();
	static void destroy();
	static void draw_sprites();
	static void sync_events();

	static void loadMusic(const char* path_to_file, int music_index);
	static bool playMusic(int music_index);
	static bool playMusic(int music_index, bool do_loop);
	static void stopMusic();

	static void setWindowSize(int width, int height);
	static void setWindowTitle(const char* title);
	static void setWindowResolution(int width, int height);
	static int getResolutionWidth();
	static int getResolutionHeight();
	static bool isWindowOpen();
	static sf::RenderWindow* getWindow();
	static void clearWindow(RGB color);
	static void setFramerateLimit(unsigned int limit);

	static bool loadImage(const char* image_file_path, int image_id);
	static void unloadImage(int image_id);
	static bool loadTexture(const char* texture_file_path, int texture_id);
	static void sprite(int sprite_id, float window_x, float window_y, int texture_id);
	static bool setSpriteTextureCoords(int sprite_id, int tex_x, int tex_y, int width, int height);
	static void deleteSprite(int sprite_id);
	static void unloadTexture(int texture_id);
	static int getSpriteWidth(int sprite_id);
	static int getSpriteHeight(int sprite_id);
	static void setSpriteVisible(int sprite_id, bool is_visible);
	static bool getSpriteVisible(int sprite_id);

	static int lastScanCode;
	static int getLastScanCode();

	static void GameLoop();
};