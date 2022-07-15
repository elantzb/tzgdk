#pragma once
#include <map>
//#include <thread>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Scancodes.h"

namespace tzgdk
{
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

	namespace admin
	{
		void init();
		void destroy();
		void draw_sprites();
		void sync_events();
	}

	void loadMusic(const char* path_to_file, int music_index);
	bool playMusic(int music_index);
	bool playMusic(int music_index, bool do_loop);
	void stopMusic();

	void setWindowSize(int width, int height);
	void setWindowTitle(const char* title);
	void setWindowResolution(float width, float height);
	float getResolutionWidth();
	float getResolutionHeight();
	bool isWindowOpen();
	sf::RenderWindow* getWindow();
	void clearWindow(RGB color);
	void setFramerateLimit(unsigned int limit);

	bool loadImage(const char* image_file_path, int image_id);
	void unloadImage(int image_id);
	bool loadTexture(const char* texture_file_path, int texture_id);
	void sprite(int sprite_id, float window_x, float window_y, int texture_id);
	bool setSpriteTextureCoords(int sprite_id, int tex_x, int tex_y, int width, int height);
	void deleteSprite(int sprite_id);
	void unloadTexture(int texture_id);
	float getSpriteWidth(int sprite_id);
	float getSpriteHeight(int sprite_id);
	void setSpriteVisible(int sprite_id, bool is_visible);
	bool getSpriteVisible(int sprite_id);

	int getLastScanCode();

	extern void GameLoop();
}
