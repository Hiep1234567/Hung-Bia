#include "Game.h"

//Private functiosn
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Hung Bia", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	this->player = new Player();
	this->speed = 1.f;
	this->player->setPosition(this->leftLimit,this->bottomLimit-this->player->getGlobalBounds().height);
}

void Game::initVariables()
{
	this->leftLimit = 58.f;
	this->rightLimit = 813.f;
	this->bottomLimit = 749.f;
	this->topLimit = 50.f;

	this->gameOverPos_x = (this->rightLimit - this->leftLimit - this->gameOverText.getGlobalBounds().width) / 2.f - this->leftLimit - 40.f;
	this->gameOverPos_y = (this->bottomLimit - this->topLimit) / 2.f - this->gameOverText.getGlobalBounds().height / 2.f - 30.f;

	this->pointPos_x = 420.f;
	this->pointPos_y = 400.f;

	this->spawnTimerMax = 5.f;
	this->spawnTimer = this->spawnTimerMax;

	this->maxEnemies = 10;

	this->point = 0;
}

void Game::initTexture()
{
	if (!this->bgText.loadFromFile("Texture/bg.png"))
		std::cout << "ERROR::GAME::INITTEXT::Could not load the texture";
	if (!this->bgText1.loadFromFile("Texture/bg1.png"))
		std::cout << "ERROR::GAME::INITTEXT::Could not load the texture";


}

void Game::initSprite()
{
	this->bgSprite.setTexture(this->bgText);
	this->bgSprite1.setTexture(this->bgText1);

}

void Game::initHeart()
{
	this->maxHeart = 3;
	float distanceHeart=198.f;
	for (size_t i = 0; i < this->maxHeart; i++)
	{
		this->hearts.push_back(new Heart(distanceHeart, 708.f));
		distanceHeart -= 50.f;
	}
}

void Game::initBackground()
{
	this->initTexture();
	this->initSprite();
	
}

void Game::initGUI()
{
	//Init font
	if (!this->font.loadFromFile("Font/VLITHOS.TTF"))
	{
		std::cout << "ERROR::GAME::LOAD FONT";
	}

	//Init point text
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::Red);
	this->text.setCharacterSize(30);
	this->text.setPosition(sf::Vector2f(679.f, 66.f));

	//Init game over text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(sf::Color(153, 153, 0));
	this->gameOverText.setCharacterSize(55);
	this->gameOverText.setPosition(this->gameOverPos_x, this->gameOverPos_y);
	this->gameOverText.setString("GAME OVER");

	//Init winner text
	this->WinnerText.setFont(this->font);
	this->WinnerText.setFillColor(sf::Color(153, 153, 0));
	this->WinnerText.setCharacterSize(50);
	this->WinnerText.setPosition(this->gameOverPos_x-100, this->gameOverPos_y);
	this->WinnerText.setString("CONGRATULATIONS");
}

void Game::initImage()
{
	
	/*this->imageSprite.setTexture(this->imageText);	
	this->imageSprite.setPosition(sf::Vector2f(880.f, 52.f));*/
}


//Con/Des
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initBackground();
	this->initPlayer();
	this->initHeart();
	this->initGUI();
	/*this->initImage();*/
}

Game::~Game()
{
	delete this->window;

	delete this->player;

	for (auto* i : this->enemies)
	{
		delete i;
	}

	for (auto* i : this->hearts)
	{
		delete i;
	}
}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvent();

		if(this->hearts.size()>0&&this->point<10000)
		{
			this->update();
			this->render();
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->updateCollision();

	this->updateEnemy();

	this->updateCombat();

	this->updateGUI();
}

void Game::updatePollEvent()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (ev.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}
}

void Game::updatePlayer()
{
	
}

void Game::updateInput()
{
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player->move(-this->speed, 0.f);
		//std::cout << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
	}

	//Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player->move(this->speed, 0.f);
	}

}

void Game::updateCollision()
{	
	//Left collision
	if (this->player->getGlobalBounds().left < this->leftLimit)
	{
		this->player->setPosition(this->leftLimit, this->player->getGlobalBounds().top);
	}

	//Right collision
	if (this->player->getGlobalBounds().left+this->player->getGlobalBounds().width > this->rightLimit)
	{
		this->player->setPosition(this->rightLimit-this->player->getGlobalBounds().width, this->player->getGlobalBounds().top);
	}
}

void Game::updateEnemy()
{
	this->spawnEnemies();
}

void Game::spawnEnemies()
{
	this->spawnTimer += 0.05f;

	if(this->spawnTimer >= this->spawnTimerMax)
	{
		if (this->enemies.size() < this->maxEnemies)
		{
			this->enemies.push_back(new Enemy(*this->window));

			this->spawnTimer = 0.f;
		}
	}
}

void Game::updateCombat()
{
	unsigned counter = 0;

	unsigned counterHeart = 0;
	
	//Update
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		if (enemy->getGlobalBounds().top + enemy->getGlobalBounds().height >this->bottomLimit)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);

			delete this->hearts.at(counterHeart);
			this->hearts.erase(this->hearts.begin() + counterHeart);
			++counterHeart;
		}

		else if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()))
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);

			this->point += 100;
		}
		++counter;
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << this->point;
	this->text.setString(ss.str());


}

void Game::render()
{
	this->window->clear();

	//Draw 

	this->window->draw(this->bgSprite);
	
	this->player->render(*this->window);

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* heart : this->hearts)
	{
		heart->render(this->window);
	}

	this->renderImage();
	
	this->renderGUI();

	this->window->draw(this->bgSprite1);

	this->window->display();
}

void Game::renderGUI()
{
	//Game over screen
	if (this->hearts.size() == 0)
	{
		this->window->draw(this->gameOverText);

		this->text.setPosition(this->pointPos_x, this->pointPos_y);

		this->text.setCharacterSize(40.f);

	}

	//Winner text
	if (this->point == 10000)
	{
		this->window->draw(this->WinnerText);
	}

	this->window->draw(this->text);
}

void Game::renderImage()
{
	if (this->point == 2000)
	{
		this->imageText.loadFromFile("Texture/1.png");
		this->imageSprite.setTexture(this->imageText);
	}
	if (this->point == 4000)
	{
		this->imageText.loadFromFile("Texture/2.png");
		this->imageSprite.setTexture(this->imageText);
	}
	if (this->point == 6000)
	{
		this->imageText.loadFromFile("Texture/3.png");
		this->imageSprite.setTexture(this->imageText);
	}
	if (this->point == 8000)
	{
		this->imageText.loadFromFile("Texture/4.png");
		this->imageSprite.setTexture(this->imageText);
	}
	this->imageSprite.setPosition(sf::Vector2f(850.f, 52.f));
	this->window->draw(this->imageSprite);
}

	