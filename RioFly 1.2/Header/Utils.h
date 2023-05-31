#pragma once

#pragma warning (disable : 4018)
#pragma warning (disable : 4353)

#include "GameConfig.h"
#include "Character.h"
#include "Background.h"
#include "Music.h"
#include "Screen.h"

class Game {
private:
	sf::RenderWindow window;
	sf::Event e;

	//texture
	sf::Texture begin_scr;
	sf::Texture end_scr;
	sf::Texture unchoose_button;
	sf::Texture choose_button;
	sf::Texture replay_unchoose_button;
	sf::Texture replay_choose_button;
	sf::Texture music_on_button;
	sf::Texture music_off_button;
	sf::Texture exit_on_button;
	sf::Texture exit_off_button;
	sf::Texture content;
	sf::Texture tutorial;
	sf::Texture next_choose_button;
	sf::Texture next_unchoose_button;
	sf::Texture pausing_scr;

	sf::Sprite sprite_pausing_screen;

	sf::Sprite  play_button;
	sf::Sprite  begin_screen;
	sf::Sprite  exit_button;
	sf::Sprite  music_button;

	bool music_on = true;
	bool in_content = true;
	bool in_screen = true;

	sf::Vector2f but_pos;

	//character's texture
	std::string linkred;
	std::string linkrio;
	std::string linkenemy;

	//main character
	Red red;
	Rio rio;
	int respawn = 0;

	//enemy
	std::vector<Enemy*> enemies;

	//diamond
	std::vector<Diamond*> diamonds;

	//rocket
	std::vector<Rocket*> rockets;

	//collision
	std::vector<CollisionDiamond*> coldiamond;
	std::vector<CollisionEnemy*> colenemy;
	std::vector<CollisionEnemy*> colrocket;

	//system
	unsigned points = 0;
	sf::Font font;
	sf::Text pointTex;
	sf::Text gameOverTex;
	sf::Text playerHpTex;
	
	//background
	Background background;
	int typeOfBackground;
	std::vector<sf::Texture> Texture_Layers;

	//Music
	sf::Music Music;
	int typeOfMusic;
	std::vector<std::string> Name_Of_Songs;
	
	//GUI
	sf::RectangleShape playerHp;
	sf::RectangleShape playerHpBack;
public:
	Game();

	bool setGame();

	void updateWhilePlaying();
	
	bool running();

	void setUp();

	void reset();

	void updateGUI();
	
	void updateCollision();
	
	void updateEnemy();

	void updateDiamond();

	void updateRocket();

	void updateNewCollision();

	void renderGUI();
};
