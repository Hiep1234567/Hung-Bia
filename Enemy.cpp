#include "Enemy.h"

void Enemy::initVariables()
{
	this->speed = 2.f;
}

void Enemy::initTexture()
{
	this->texture.loadFromFile("Texture/bia.png");
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->texture);
}

void Enemy::setPosition(sf::RenderWindow& window)
{
	this->sprite.setPosition(sf::Vector2f(rand()% (759-40)+40, 0.f));
}



Enemy::Enemy(sf::RenderWindow& window)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->setPosition(window);
}

Enemy::~Enemy()
{
}

sf::FloatRect Enemy::getGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

void Enemy::update()
{
	this->sprite.move(0.f, this->speed);
}



void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
