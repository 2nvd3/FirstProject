#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include "GameConfig.h"
#include "Enemy.h"
#include "Diamond.h"
#include "Character.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

class Game {
private:
	sf::RenderWindow* window;

	//player
	Character* character;

	//enemy
	std::vector<Enemy*> enemies;
	float spawnTimer;
	float spawnTimerMax;

	//diamond
	std::vector<Diamond*> diamonds;
	float spawnTimerdiamond;
	float spawnTimerMaxdiamond;

	//system
	unsigned points;
	sf::Font font;
	sf::Text pointTex;
	sf::Text gameOverTex;

	//background
	sf::Texture backgroundTex;
	sf::Sprite background;

	//playerGUI
	sf::RectangleShape playerHp;
	sf::RectangleShape playerHpBack;	

	void initWindow();

	void initEnemy();
	void initDiamond();
	void initCharacter();

	void initBackground();

	void initSystem();

	void initGUI();
public:

	Game();

	void run();

	void updatePollEvent();
	void updateKey();
	void updateGUI();
	void update();
	void updateBackground();
	void updateCollision();

	void updateEnemy();
	void updateDiamond();

	void render();
	void renderBackground();
	void renderGUI();
};
