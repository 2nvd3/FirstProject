#pragma once

#include "GameConfig.h"
#include "Character.h"
#include "Background.h"
#include "Music.h"

class Game {
private:
	sf::RenderWindow window;
  
	//player
	Character character;
	Bird bird;
  
	//enemy
	std::vector<Enemy*> enemies;
  
	//diamond
	std::vector<Diamond*> diamonds;
  
	//system
	unsigned points;
	sf::Font font;
	sf::Text pointTex;
	sf::Text gameOverTex;

	sf::Texture texture_contents;
	sf::Texture texture_tutor;
	sf::Sprite content;
	sf::Sprite tutor;
  
	//background
	Background background;
	int typeOfBackground;
	std::vector<sf::Texture> Texture_Layers;
	//sf::Texture backgroundTex;
	//sf::Sprite background;

	int typeOfMusic;
	sf::Music Music;
	std::vector<std::string> Name_Of_Songs;
	
	//playerGUI
	sf::RectangleShape playerHp;
	sf::RectangleShape playerHpBack;	

	void initWindow();
	void initMusic();
	void initScreen();
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
