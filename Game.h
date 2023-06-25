#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Heart.h"

class Game
{
private:
	sf::RenderWindow* window;
	//Heart variables
	float heartPos_x, heartPos_y;

	//Player
	Player* player;
	float speed;

	//Background;
	sf::Texture bgText;
	sf::Sprite bgSprite;

	sf::Texture bgText1;
	sf::Sprite bgSprite1;

	//Image
	sf::Texture imageText;
	sf::Sprite imageSprite;

	float leftLimit, rightLimit, topLimit, bottomLimit;

	//Enemy 
	std::vector<Enemy*> enemies;
	float enemySpeed;
	float spawnTimer;
	float spawnTimerMax;
	int maxEnemies;

	//Heart
	std::vector<Heart*> hearts;
	float maxHeart;

	//System
	float point;
	float pointPos_x, pointPos_y;

	//GUI
	sf::Font font;
	sf::Text text;

	//Game over
	sf::Text gameOverText;
	float gameOverPos_x, gameOverPos_y;

	//Winner
	sf::Text WinnerText;

	//Private functions
	void initWindow();
	void initPlayer();
	void initVariables();
	void initTexture();
	void initSprite();
	void initHeart();
	void initBackground();
	void initGUI();
	void initImage();

public:
	Game();
	virtual~Game();

	//Functions
	void run();

	void update();
	void updatePollEvent();
	void updatePlayer();
	void updateInput();
	void updateCollision();
	void updateEnemy();
	void spawnEnemies();
	void updateCombat();
	void updateGUI();

	void render();
	void renderGUI();
	void renderImage();
};

