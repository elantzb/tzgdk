// tzgdk-lib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "tzgdk-lib.h"


// ADMIN //

int TZGDK::lastScanCode = -1;

void TZGDK::init()
{
	TZGDK::getInstance().musicMap = new std::map<int, const char*>;

	TZGDK::getInstance().currentMusic = new sf::Music;

	TZGDK::getInstance().window = new sf::RenderWindow(sf::VideoMode(320, 320, 32), "My Window");
	//(*(TZGDK::getInstance().window)).setSize(sf::Vector2u(64, 64));

	TZGDK::getInstance().loadedImages = new std::map<int, sf::Image*>;

	TZGDK::getInstance().loadedTextures = new std::map<int, sf::Texture*>;

	TZGDK::getInstance().loadedSprites = new std::map<int, SpriteWrapper>;
}

void TZGDK::destroy()
{
	TZGDK::getInstance().loadedSprites->clear();
	delete TZGDK::getInstance().loadedSprites;

	TZGDK::getInstance().loadedTextures->clear();
	delete TZGDK::getInstance().loadedTextures;

	TZGDK::getInstance().loadedImages->clear();
	delete TZGDK::getInstance().loadedImages;

	TZGDK::getInstance().window->~RenderWindow();
	delete TZGDK::getInstance().window;

	TZGDK::getInstance().currentMusic->stop();
	TZGDK::getInstance().currentMusic->~Music();
	delete TZGDK::getInstance().currentMusic;

	TZGDK::getInstance().musicMap->clear();
	delete TZGDK::getInstance().musicMap;
	
}

void TZGDK::draw_sprites()
{
	auto it = TZGDK::getInstance().loadedSprites->begin();
	auto end = TZGDK::getInstance().loadedSprites->end();
	for (; it != end; ++it)
	{
		SpriteWrapper currentSprite = it->second;

		if(currentSprite.isVisible)
			TZGDK::getWindow()->draw(*(currentSprite.sprite));
	}
}

void TZGDK::sync_events()
{
	TZGDK::lastScanCode = -1;
}

// MUSIC //

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

// WINDOW //

void TZGDK::setWindowSize(int width, int height)
{
	TZGDK::getInstance().window->setSize(sf::Vector2u(width, height));
}

void TZGDK::setWindowTitle(const char* title)
{
	(*(TZGDK::getInstance().window)).setTitle(title);
}

void TZGDK::setWindowResolution(float width, float height)
{
	/// TODO: Make a solution for automatically sizing the viewport inside the window without stretching
	/// using black bars on sides or top/bottom depending on the situation.
	TZGDK::getInstance().window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
}

float TZGDK::getResolutionWidth()
{
	return TZGDK::getInstance().window->getView().getSize().x;
}

float TZGDK::getResolutionHeight()
{
	return TZGDK::getInstance().window->getView().getSize().y;
}

bool TZGDK::isWindowOpen()
{
	return TZGDK::getInstance().window->isOpen();
}

sf::RenderWindow* TZGDK::getWindow()
{
	return TZGDK::getInstance().window;
}

void TZGDK::clearWindow(RGB color)
{
	(*(TZGDK::getInstance().window)).clear(sf::Color(color.r, color.g, color.b, 255));
}

void TZGDK::setFramerateLimit(unsigned int limit)
{
	TZGDK::getInstance().window->setFramerateLimit(limit);
}

// TEXTURES AND SPRITES //

bool TZGDK::loadImage(const char* image_file_path, int image_id)
{
	sf::Image* new_image = new sf::Image;
	if (!(new_image->loadFromFile(image_file_path)))
		return false;

	(*(TZGDK::getInstance().loadedImages)).insert_or_assign(image_id, new_image);

	return true;
}

void TZGDK::unloadImage(int image_id)
{
	(*(TZGDK::getInstance().loadedImages)).erase(image_id);
}

bool TZGDK::loadTexture(const char* texture_file_path, int texture_id)
{
	sf::Texture* new_texture = new sf::Texture;
	if (!(new_texture->loadFromFile(texture_file_path)))
		return false;

	(*(TZGDK::getInstance().loadedTextures)).insert_or_assign(texture_id, new_texture);

	return true;
}

void TZGDK::sprite(int sprite_id, float window_x, float window_y, int texture_id)
{
	sf::Sprite* sprite;
	if (!(*(TZGDK::getInstance().loadedSprites)).count(sprite_id))
	{
		sprite = new sf::Sprite;
		
		(*(TZGDK::getInstance().loadedSprites)).insert_or_assign(sprite_id, sprite);
	}
	else
	{
		sprite = (*(TZGDK::getInstance().loadedSprites)).at(sprite_id).sprite;
	}

	sf::Texture* tex = (*(TZGDK::getInstance().loadedTextures)).at(texture_id);

	sprite->setTexture(*tex);
	sprite->setPosition(sf::Vector2f(window_x, window_y));
}

bool TZGDK::setSpriteTextureCoords(int sprite_id, int tex_x, int tex_y, int width, int height)
{
	sf::Sprite* sprite;
	if (!(*(TZGDK::getInstance().loadedSprites)).count(sprite_id))
		return false;
	else
	{
		sprite = (*(TZGDK::getInstance().loadedSprites)).at(sprite_id).sprite;
	}

	sprite->setTextureRect(sf::IntRect(tex_x, tex_y, width, height));

	return true;
}

void TZGDK::deleteSprite(int sprite_id)
{
	TZGDK::getInstance().loadedSprites->erase(sprite_id);
}

void TZGDK::unloadTexture(int texture_id)
{
	(*(TZGDK::getInstance().loadedTextures)).erase(texture_id);
}

float TZGDK::getSpriteWidth(int sprite_id)
{
	return TZGDK::getInstance().loadedSprites->at(sprite_id).sprite->getLocalBounds().width;
}

float TZGDK::getSpriteHeight(int sprite_id)
{
	return TZGDK::getInstance().loadedSprites->at(sprite_id).sprite->getLocalBounds().height;
}

void TZGDK::setSpriteVisible(int sprite_id, bool is_visible)
{
	TZGDK::getInstance().loadedSprites->at(sprite_id).isVisible = is_visible;
}

bool TZGDK::getSpriteVisible(int sprite_id)
{
	return TZGDK::getInstance().loadedSprites->at(sprite_id).isVisible;
}

// INPUT //

int TZGDK::getLastScanCode()
{
	return TZGDK::lastScanCode;
}

// MAIN //

int main(char* args[], int nargs)
{
	TZGDK::init();
	while (TZGDK::isWindowOpen())
	{
		sf::Event event;
		while ((*(TZGDK::getWindow())).pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				TZGDK::getWindow()->close();
				break;

			case sf::Event::KeyPressed:
				TZGDK::lastScanCode = event.key.code;
				tzgdk::admin::trigger_scancode(event.key.code);
				break;

			case sf::Event::KeyReleased:
				tzgdk::admin::untrigger_scancode(event.key.code);
				break;

			default:
				break;
			}
		}

		TZGDK::GameLoop();

		TZGDK::draw_sprites();
		TZGDK::sync_events();
		TZGDK::getWindow()->display();
	}

	TZGDK::destroy();

	return 0;
}