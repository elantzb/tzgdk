// tzgdk-lib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "tzgdk-lib.h"


namespace tzgdk
{
	namespace admin
	{
		// ADMIN //

		int lastScanCode = -1;

		std::map<int, const char*>* musicMap;
		sf::Music* currentMusic;

		sf::RenderWindow* window;

		std::map<int, sf::Image*>* loadedImages;
		std::map<int, sf::Texture*>* loadedTextures;
		std::map<int, SpriteWrapper>* loadedSprites;

		/// TODO: Investigate multi-threading for drawing
		//std::thread* drawThread;

		void init()
		{
			musicMap = new std::map<int, const char*>;

			currentMusic = new sf::Music;

			admin::window = new sf::RenderWindow(sf::VideoMode(320, 320, 32), "My Window");

			loadedImages = new std::map<int, sf::Image*>;

			loadedTextures = new std::map<int, sf::Texture*>;

			loadedSprites = new std::map<int, SpriteWrapper>;
		}

		void destroy()
		{
			loadedSprites->clear();
			delete loadedSprites;

			loadedTextures->clear();
			delete loadedTextures;

			loadedImages->clear();
			delete loadedImages;

			admin::window->~RenderWindow();
			delete admin::window;

			currentMusic->stop();
			currentMusic->~Music();
			delete currentMusic;

			musicMap->clear();
			delete musicMap;

		}

		void draw_sprites()
		{
			auto it = loadedSprites->begin();
			auto end = loadedSprites->end();
			for (; it != end; ++it)
			{
				SpriteWrapper currentSprite = it->second;

				if (currentSprite.isVisible)
					getWindow()->draw(*(currentSprite.sprite));
			}
		}

		void sync_events()
		{
			lastScanCode = -1;
		}
	}

	// MUSIC //

	void loadMusic(const char* path_to_file, int music_index)
	{
		admin::musicMap->insert_or_assign(music_index, path_to_file);
	}

	bool playMusic(int music_index)
	{
		const char* musicPath = admin::musicMap->at(music_index);
		if (!admin::currentMusic->openFromFile(musicPath))
			return false;

		admin::currentMusic->play();

		return true;
	}

	bool playMusic(int music_index, bool do_loop)
	{
		const char* musicPath = admin::musicMap->at(music_index);
		if (!admin::currentMusic->openFromFile(musicPath))
			return false;

		admin::currentMusic->setLoop(true);
		admin::currentMusic->play();

		return true;
	}

	void stopMusic()
	{
		admin::currentMusic->stop();
	}

	// WINDOW //

	void setWindowSize(int width, int height)
	{
		admin::window->setSize(sf::Vector2u(width, height));
	}

	void setWindowTitle(const char* title)
	{
		admin::window->setTitle(title);
	}

	void setWindowResolution(float width, float height)
	{
		/// TODO: Make a solution for automatically sizing the viewport inside the admin::window without stretching
		/// using black bars on sides or top/bottom depending on the situation.
		admin::window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
	}

	float getResolutionWidth()
	{
		return admin::window->getView().getSize().x;
	}

	float getResolutionHeight()
	{
		return admin::window->getView().getSize().y;
	}

	bool isWindowOpen()
	{
		return admin::window->isOpen();
	}

	sf::RenderWindow* getWindow()
	{
		return admin::window;
	}

	void clearWindow(RGB color)
	{
		admin::window->clear(sf::Color(color.r, color.g, color.b, 255));
	}

	void setFramerateLimit(unsigned int limit)
	{
		admin::window->setFramerateLimit(limit);
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

	void sprite(int sprite_id, float window_x, float window_y, int texture_id)
	{
		sf::Sprite* sprite;
		if (!admin::loadedSprites->count(sprite_id))
		{
			sprite = new sf::Sprite;

			admin::loadedSprites->insert_or_assign(sprite_id, sprite);
		}
		else
		{
			sprite = admin::loadedSprites->at(sprite_id).sprite;
		}

		sf::Texture* tex = admin::loadedTextures->at(texture_id);

		sprite->setTexture(*tex);
		sprite->setPosition(sf::Vector2f(window_x, window_y));
	}

	bool setSpriteTextureCoords(int sprite_id, int tex_x, int tex_y, int width, int height)
	{
		sf::Sprite* sprite;
		if (!admin::loadedSprites->count(sprite_id))
			return false;
		else
		{
			sprite = admin::loadedSprites->at(sprite_id).sprite;
		}

		sprite->setTextureRect(sf::IntRect(tex_x, tex_y, width, height));

		return true;
	}

	void deleteSprite(int sprite_id)
	{
		admin::loadedSprites->erase(sprite_id);
	}

	void unloadTexture(int texture_id)
	{
		admin::loadedTextures->erase(texture_id);
	}

	float getSpriteWidth(int sprite_id)
	{
		return admin::loadedSprites->at(sprite_id).sprite->getLocalBounds().width;
	}

	float getSpriteHeight(int sprite_id)
	{
		return admin::loadedSprites->at(sprite_id).sprite->getLocalBounds().height;
	}

	void setSpriteVisible(int sprite_id, bool is_visible)
	{
		admin::loadedSprites->at(sprite_id).isVisible = is_visible;
	}

	bool getSpriteVisible(int sprite_id)
	{
		return admin::loadedSprites->at(sprite_id).isVisible;
	}

	// INPUT //

	int getLastScanCode()
	{
		return admin::lastScanCode;
	}

}

// MAIN //

int main(char* args[], int nargs)
{
	tzgdk::admin::init();
	while (tzgdk::isWindowOpen())
	{
		sf::Event event;
		while (tzgdk::getWindow()->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				tzgdk::getWindow()->close();
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
		tzgdk::getWindow()->display();
	}

	tzgdk::admin::destroy();

	return 0;
}