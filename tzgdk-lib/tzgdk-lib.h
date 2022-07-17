#pragma once
#include <map>
//#include <thread>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Scancodes.h"

#define MAX_SPRITE_PRIORITIES 32

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
		int textureCols, textureRows;
		int spriteFrame;
		SpriteWrapper(sf::Sprite* p_sprite, int texture_cols = 0, int texture_rows = 0, int sprite_frame = 0)
		{
			sprite = p_sprite;
			isVisible = true;
			textureCols = texture_cols;
			textureRows = texture_rows;
			spriteFrame = sprite_frame;
		}
	};

	namespace admin
	{
		void init();
		void destroy();
		void draw_sprites();
		void sync_events();

		bool textureExists(int texture_id);
		sf::Texture* getTexture(int texture_id);
		
		bool spriteExists(int sprite_id);
		SpriteWrapper* getSprite(int sprite_id);
	}

	void loadMusic(const char* path_to_file, int music_index);
	bool playMusic(int music_index, bool do_loop = false);
	void stopMusic(int music_index);
	bool musicPlaying(int music_index);
	bool musicLooping(int music_index);

	void setWindowSize(int width, int height);
	void setWindowTitle(const char* title);
	void setWindowResolution(float width, float height);
	float getResolutionWidth();
	float getResolutionHeight();
	bool isWindowOpen();
	sf::RenderWindow* getRenderWindow();
	void clearWindow(RGB color);
	void setFramerateLimit(unsigned int limit);

	bool loadImage(const char* image_file_path, int image_id);
	void unloadImage(int image_id);
	bool loadTexture(const char* texture_file_path, int texture_id);
	void sprite(int sprite_id, float window_x, float window_y, int texture_id, bool is_visible = true);
	bool setSpriteTextureCoords(int sprite_id, int tex_x, int tex_y, int width, int height);
	void setSpriteTextureCoordsNormalized(int sprite_id, float tex_x_n, float tex_y_n, float width_n, float height_n, int texture_id);
	void deleteSprite(int sprite_id);
	void unloadTexture(int texture_id);
	float getSpriteWidth(int sprite_id);
	float getSpriteHeight(int sprite_id);
	void setSpriteVisible(int sprite_id, bool is_visible);
	bool getSpriteVisible(int sprite_id);
	float getSpriteX(int sprite_id);
	float getSpriteY(int sprite_id);
	void setSpritePriority(int sprite_id, const short priority);
	float getSpriteTop(int sprite_id);
	float getSpriteRight(int sprite_id);
	float getSpriteBottom(int sprite_id);
	float getSpriteLeft(int sprite_id);
	bool testSpriteOverlap(int sprite_1, int sprite_2);
	void setSpriteScale(int sprite_id, float scale_x, float scale_y);
	void createAnimatedSprite(int sprite_id, const char* image_file_path, int cols, int rows, int texture_id);
	void setSpriteFrame(int sprite_id, int sprite_frame, int texture_id);
	int getSpriteFrame(int sprite_id);

	int getLastScanCode(); /// TODO: move this to Scancodes files

	const int getMilliTime();

	extern void GameLoop();
}
