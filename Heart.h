#pragma once

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Heart
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	void initTexture();
	void initSprite();
public:
	Heart(const float x, const float y);
	virtual~Heart();

	void update();
	void render(sf::RenderTarget* target);

};

