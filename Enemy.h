#pragma once

#include <iostream>
#include <vector>
#include <sstream>

#include <SFML\Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Enemy
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float speed;

	//Functions
	void initVariables();
	void initTexture();
	void initSprite();
	void setPosition(sf::RenderWindow& window);
public:
	Enemy(sf::RenderWindow&window);
	virtual~Enemy();

	//Accessors
	sf::FloatRect getGlobalBounds();

	//Functions
	void update();

	void render(sf::RenderTarget* target);
};

