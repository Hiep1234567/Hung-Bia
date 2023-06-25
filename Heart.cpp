#include "Heart.h"

void Heart::initTexture()
{
	this->texture.loadFromFile("Texture/heart.png");
}

void Heart::initSprite()
{
	this->sprite.setTexture(this->texture);
}

Heart::Heart(const float x,const float y)
{
	this->initTexture();
	this->initSprite();

	this->sprite.setPosition(x, y);
}

Heart::~Heart()
{
}

void Heart::update()
{
}

void Heart::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
