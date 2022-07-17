// tzgdk-lib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "tzgdk-lib.h"

#include <iostream>

namespace tzgdk
{
	namespace admin
	{
		// ADMIN //

		int lastScanCode = -1;

		std::map<int, const char*>* musicMap;
		std::map<int, sf::Music*>* playingMusics;

		//sf::Window* window;
		sf::RenderWindow* renderWindow;

		std::map<int, sf::Image*>* loadedImages;
		std::map<int, sf::Texture*>* loadedTextures;
		std::map<int, SpriteWrapper*>* loadedSprites;
		std::vector<int>** spritePriorities;

		/// TODO: Investigate multi-threading for drawing
		//std::thread* drawThread;

		sf::Clock elapsedTimer;

		void init()
		{
			musicMap = new std::map<int, const char*>;

			playingMusics = new std::map<int, sf::Music*>;

			//window = new sf::Window(sf::VideoMode(320, 320, 32), "My Window");
			renderWindow = new sf::RenderWindow(sf::VideoMode(320, 320, 32), "My Window");

			loadedImages = new std::map<int, sf::Image*>;

			loadedTextures = new std::map<int, sf::Texture*>;

			loadedSprites = new std::map<int, SpriteWrapper*>;

			spritePriorities = (std::vector<int>**)malloc(sizeof(std::vector<int>) * MAX_SPRITE_PRIORITIES);
			for (int i = 0; i < MAX_SPRITE_PRIORITIES; i++)
			{
				spritePriorities[i] = new std::vector<int>;
			}
		}

		void destroy()
		{
			for (int i = 0; i < MAX_SPRITE_PRIORITIES; i++)
			{
				spritePriorities[i]->clear();
				delete spritePriorities[i];
			}
			delete spritePriorities;

			loadedSprites->clear();
			delete loadedSprites;

			loadedTextures->clear();
			delete loadedTextures;

			loadedImages->clear();
			delete loadedImages;

			admin::renderWindow->~RenderWindow();
			delete admin::renderWindow;

			for (auto it = playingMusics->begin(); it != playingMusics->end(); it++)
			{
				sf::Music* currentMusic = it->second;
				currentMusic->stop();
				currentMusic->~Music();
				delete currentMusic;
			}
			playingMusics->clear();
			delete playingMusics;

			musicMap->clear();
			delete musicMap;

		}

		void draw_sprites()
		{
			/*auto it = loadedSprites->begin();
			auto end = loadedSprites->end();
			for (; it != end; ++it)
			{
				SpriteWrapper currentSprite = it->second;

				if (currentSprite.isVisible)
					getWindow()->draw(*(currentSprite.sprite));
			}*/

			for (int i = 0; i < MAX_SPRITE_PRIORITIES; i++)
			{
				auto it = admin::spritePriorities[i]->begin();
				auto end = admin::spritePriorities[i]->end();
				for (; it < end; it++)
				{
					SpriteWrapper* currentSprite = loadedSprites->at(*it);

					if (currentSprite->isVisible)
						getRenderWindow()->draw(*(currentSprite->sprite));
				}
			}
		}

		void sync_events()
		{
			lastScanCode = -1;
		}

		bool textureExists(int texture_id)
		{
			return loadedTextures->count(texture_id) > 0;
		}

		sf::Texture* getTexture(int texture_id)
		{
			return loadedTextures->at(texture_id);
		}

		bool spriteExists(int sprite_id)
		{
			return loadedSprites->count(sprite_id) > 0;
		}

		SpriteWrapper* getSprite(int sprite_id)
		{
			return loadedSprites->at(sprite_id);
		}
	}

	// MUSIC //

	void loadMusic(const char* path_to_file, int music_index)
	{
		admin::musicMap->insert_or_assign(music_index, path_to_file);
	}

	bool playMusic(int music_index, bool do_loop)
	{
		const char* musicPath = admin::musicMap->at(music_index);
		sf::Music* newMusic = new sf::Music;
		if (!newMusic->openFromFile(musicPath))
			return false;

		newMusic->setLoop(do_loop);
		newMusic->play();
		admin::playingMusics->insert_or_assign(music_index, newMusic);

		return true;
	}

	void stopMusic(int music_index)
	{
		admin::playingMusics->at(music_index)->stop();
	}

	bool musicLooping(int music_index)
	{
		if(admin::playingMusics->count(music_index) > 0)
			return admin::playingMusics->at(music_index)->getLoop();
		return false;
	}

	bool musicPlaying(int music_index)
	{
		if(!admin::playingMusics->count(music_index))
			return false;

		return admin::playingMusics->at(music_index)->getStatus() == sf::SoundSource::Status::Playing;
	}

	// WINDOW //

	void setWindowSize(int width, int height)
	{
		admin::renderWindow->setSize(sf::Vector2u(width, height));
	}

	void setWindowTitle(const char* title)
	{
		admin::renderWindow->setTitle(title);
	}

	void setWindowResolution(float width, float height)
	{
		/// TODO: Make a solution for automatically sizing the viewport inside the admin::window without stretching
		/// using black bars on sides or top/bottom depending on the situation.
		admin::renderWindow->setView(sf::View(sf::FloatRect(0, 0, width, height)));
	}

	float getResolutionWidth()
	{
		return admin::renderWindow->getView().getSize().x;
	}

	float getResolutionHeight()
	{
		return admin::renderWindow->getView().getSize().y;
	}

	bool isWindowOpen()
	{
		return admin::renderWindow->isOpen();
	}

	sf::RenderWindow* getRenderWindow()
	{
		return admin::renderWindow;
	}

	void clearWindow(RGB color)
	{
		admin::renderWindow->clear(sf::Color(color.r, color.g, color.b, 255));
	}

	void setFramerateLimit(unsigned int limit)
	{
		admin::renderWindow->setFramerateLimit(limit);
	}

	// TEXTURES AND SPRITES //

	bool loadImage(const char* image_file_path, int image_id)
	{
		sf::Image* new_image = new sf::Image;
		if (!(new_image->loadFromFile(image_file_path)))
			return false;

		admin::loadedImages->insert_or_assign(image_id, new_image);

		return true;
	}

	void unloadImage(int image_id)
	{
		admin::loadedImages->erase(image_id);
	}

	bool loadTexture(const char* texture_file_path, int texture_id)
	{
		sf::Texture* new_texture = new sf::Texture;
		if (!(new_texture->loadFromFile(texture_file_path)))
			return false;

		admin::loadedTextures->insert_or_assign(texture_id, new_texture);

		return true;
	}

	void sprite(int sprite_id, float window_x, float window_y, int texture_id, bool is_visible)
	{
		if (!admin::textureExists(texture_id))
			return;

		sf::Sprite* sprite;
		if (!admin::spriteExists(sprite_id))
		{
			sprite = new sf::Sprite;
			SpriteWrapper* sw = new SpriteWrapper(sprite);

			admin::loadedSprites->insert_or_assign(sprite_id, sw);
			admin::spritePriorities[0]->push_back(sprite_id);

			//std::cout << "Setting sprite " << sprite_id << " to priority 0" << std::endl;
		}
		else
		{
			sprite = admin::getSprite(sprite_id)->sprite;
		}

		sf::Texture* tex = admin::getTexture(texture_id);

		sprite->setTexture(*tex);
		sprite->setPosition(sf::Vector2f(window_x, window_y));
	}

	bool setSpriteTextureCoords(int sprite_id, int tex_x, int tex_y, int width, int height)
	{
		sf::Sprite* sprite;
		if (!admin::spriteExists(sprite_id))
			return false;
		else
		{
			sprite = admin::getSprite(sprite_id)->sprite;
		}

		sprite->setTextureRect(sf::IntRect(tex_x, tex_y, width, height));

		return true;
	}

	void setSpriteTextureCoordsNormalized(int sprite_id, float tex_x_n, float tex_y_n, float width_n, float height_n, int texture_id)
	{
		sf::Vector2u textureBounds = admin::getTexture(texture_id)->getSize();

		int tex_x = (int)(textureBounds.x * tex_x_n);
		int tex_y = (int)(textureBounds.y * tex_y_n);
		int width = (int)(textureBounds.x * width_n);
		int height = (int)(textureBounds.y * height_n);

		setSpriteTextureCoords(sprite_id, tex_x, tex_y, width, height);
	}

	void deleteSprite(int sprite_id)
	{
		admin::loadedSprites->erase(sprite_id);
		for (int i = 0; i < MAX_SPRITE_PRIORITIES; i++)
		{
			auto it = admin::spritePriorities[i]->begin();
			auto end = admin::spritePriorities[i]->end();
			for (; it < end; it++)
			{
				if (*it == sprite_id)
				{
					admin::spritePriorities[i]->erase(it);
					//std::cout << "Removing sprite " << sprite_id << " from priority " << i << std::endl;
					break;
				}
			}
		}
	}

	void unloadTexture(int texture_id)
	{
		admin::loadedTextures->erase(texture_id);
	}

	float getSpriteWidth(int sprite_id)
	{
		if (!admin::spriteExists(sprite_id))
			return 0.0f;

		return admin::getSprite(sprite_id)->sprite->getLocalBounds().width;
	}

	float getSpriteHeight(int sprite_id)
	{
		if (!admin::spriteExists(sprite_id))
			return 0.0f;

		return admin::getSprite(sprite_id)->sprite->getLocalBounds().height;
	}

	void setSpriteVisible(int sprite_id, bool is_visible)
	{
		admin::getSprite(sprite_id)->isVisible = is_visible;
	}

	bool getSpriteVisible(int sprite_id)
	{
		return admin::loadedSprites->at(sprite_id)->isVisible;
	}

	float getSpriteX(int sprite_id)
	{
		if (!admin::spriteExists(sprite_id))
			return 0.0f;

		return admin::getSprite(sprite_id)->sprite->getPosition().x;
	}

	float getSpriteY(int sprite_id)
	{
		if (!admin::spriteExists(sprite_id))
			return 0.0f;

		return admin::loadedSprites->at(sprite_id)->sprite->getPosition().y;
	}

	void setSpritePriority(int sprite_id, const short priority)
	{
		if (priority >= MAX_SPRITE_PRIORITIES)
		{
			//std::cout << "Tried to set sprite priority too high: " << priority << std::endl;
			return;
		}

		for (int i = 0; i < MAX_SPRITE_PRIORITIES; i++)
		{
			auto it = admin::spritePriorities[i]->begin();
			auto end = admin::spritePriorities[i]->end();
			for (; it < end; it++)
			{
				if (*it == sprite_id)
				{
					admin::spritePriorities[i]->erase(it);
					//std::cout << "Removing sprite " << sprite_id << " from priority " << i << std::endl;
					break;
				}
			}
		}

		//std::cout << "Adding sprite " << sprite_id << " to priority " << priority << std::endl;
		admin::spritePriorities[priority]->push_back(sprite_id);
	}

	float getSpriteTop(int sprite_id)
	{
		return admin::loadedSprites->at(sprite_id)->sprite->getGlobalBounds().top;
	}

	float getSpriteRight(int sprite_id)
	{
		sf::FloatRect bounds = admin::getSprite(sprite_id)->sprite->getGlobalBounds();
		return bounds.left + bounds.width;
	}

	float getSpriteBottom(int sprite_id)
	{
		sf::FloatRect bounds = admin::getSprite(sprite_id)->sprite->getGlobalBounds();
		return bounds.top + bounds.height;
	}

	float getSpriteLeft(int sprite_id)
	{
		return admin::getSprite(sprite_id)->sprite->getGlobalBounds().left;
	}

	bool testSpriteOverlap(int sprite_1, int sprite_2)
	{
		if (!admin::spriteExists(sprite_1) || !admin::spriteExists(sprite_2))
			return false;

		sf::FloatRect bounds1 = admin::getSprite(sprite_1)->sprite->getGlobalBounds();
		sf::FloatRect bounds2 = admin::getSprite(sprite_2)->sprite->getGlobalBounds();

		return bounds1.left < (bounds2.left + bounds2.width) &&
			bounds2.left < (bounds1.left + bounds1.width) &&
			bounds1.top < (bounds2.top + bounds2.height) &&
			bounds2.top < (bounds1.top + bounds1.height);
	}

	void setSpriteScale(int sprite_id, float scale_x, float scale_y)
	{
		admin::getSprite(sprite_id)->sprite->setScale(scale_x, scale_y);
	}

	void createAnimatedSprite(int sprite_id, const char* image_file_path, int cols, int rows, int texture_id)
	{
		if (!admin::textureExists(texture_id))
			loadTexture(image_file_path, texture_id);

		sprite(sprite_id, 0, 0, texture_id, false);
		admin::getSprite(sprite_id)->textureCols = cols;
		admin::getSprite(sprite_id)->textureRows = rows;

		sf::Vector2u textureBounds = admin::getTexture(texture_id)->getSize();
		setSpriteTextureCoords(sprite_id, 0, 0, textureBounds.x / cols, textureBounds.y / rows);

	}

	void setSpriteFrame(int sprite_id, int sprite_frame, int texture_id)
	{
		if (!admin::spriteExists(sprite_id) || !admin::textureExists(texture_id))
			return;
		SpriteWrapper* sw = admin::getSprite(sprite_id);
		sf::Vector2u textureBounds = admin::getTexture(texture_id)->getSize();

		sw->spriteFrame = sprite_frame;

		//std::cout << "For frame " << sprite_frame << ", texture bounds " << textureBounds.x << ", " << textureBounds.y << std::endl;
		//std::cout << " and wrapper data of cols=" << sw.textureCols << " rows=" << sw.textureRows << std::endl;

		int frameWidth = textureBounds.x / sw->textureCols;
		int frameHeight = textureBounds.y / sw->textureRows;

		int w = textureBounds.x / sw->textureCols;
		int h = textureBounds.y / sw->textureRows;

		int col = sprite_frame % sw->textureCols;
		int row = (sprite_frame - col) / sw->textureRows;

		//std::cout << "picked col " << col << " and row " << row << std::endl;

		setSpriteTextureCoords(sprite_id, col * frameWidth, row * frameHeight, w, h);
	}

	int getSpriteFrame(int sprite_id)
	{
		if (!admin::spriteExists(sprite_id))
			return -1;

		return admin::getSprite(sprite_id)->spriteFrame;
	}

	// INPUT //

	int getLastScanCode()
	{
		return admin::lastScanCode;
	}

	// TIME //

	const int getMilliTime()
	{
		return admin::elapsedTimer.getElapsedTime().asMilliseconds();
	}

}

// MAIN //

int main(char* args[], int nargs)
{
	tzgdk::admin::init();
	while (tzgdk::isWindowOpen())
	{
		sf::Event event;
		while (tzgdk::getRenderWindow()->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				tzgdk::getRenderWindow()->close();
				break;

			case sf::Event::KeyPressed:
				tzgdk::admin::lastScanCode = event.key.code;
				tzgdk::admin::trigger_scancode(event.key.code);
				break;

			case sf::Event::KeyReleased:
				tzgdk::admin::untrigger_scancode(event.key.code);
				break;

			default:
				break;
			}
		}

		tzgdk::GameLoop();

		tzgdk::admin::draw_sprites();
		tzgdk::admin::sync_events();
		tzgdk::getRenderWindow()->display();
	}

	tzgdk::admin::destroy();

	//std::cin.sync();
	//std::cin.get();

	return 0;
}