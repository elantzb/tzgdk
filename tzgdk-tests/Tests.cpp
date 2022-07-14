#include <iostream>
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include "../tzgdk-lib/tzgdk-lib.h"

int main(char* args[], int nargs)
{
	TZGDK::init();

	TZGDK::loadMusic("assets/sounds/stream/underground.flac", 1);
	int musicIdx = TZGDK::playMusic(1);

	sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");


	sf::Texture texture;
	texture.loadFromFile("assets/images/spritesheets/map.bmp");

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
	sprite.setPosition(sf::Vector2f(400 - 16, 300 - 16));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);

		window.draw(sprite);

		window.display();
	}

	TZGDK::stopMusic();
	TZGDK::destroy();

	//std::cin.sync();
	//std::cin.get();

	return 0;
}

