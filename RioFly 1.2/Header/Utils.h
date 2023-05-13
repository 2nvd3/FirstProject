
#pragma once

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

	//item
	sf::Texture textureScreenBegin;
	sf::Texture textureScreenEnd;
	sf::Texture texture_play_unchoose;
	sf::Texture texture_play_choosen;
	sf::Texture texture_replay_unchoose;
	sf::Texture texture_replay_choosen;
	sf::Texture texture_music_on;
	sf::Texture texture_music_off;
	sf::Texture texture_exit_on;
	sf::Texture texture_exit_off;
	sf::Texture texture_contents;
	sf::Texture texture_next_choosen;
	sf::Texture texture_next_unchoose;
	sf::Texture texture_tutor;
	sf::Texture texture_pausing_screen;

	sf::Sprite sprite_pausing_screen;

	sf::Sprite  play_button;
	sf::Sprite  screenBegin;
	sf::Sprite  exit_button;
	sf::Sprite  music_button;

	bool Music_On = true;
	bool at_content = true;
	bool inScreen = true;

	sf::Vector2f but_pos;

	//texture
	std::string linkred;
	std::string linkrio;
	std::string linkenemy;

	//player
	Character character;
	Bird bird;
	int respawn = 0;

	//enemy
	std::vector<Enemy*> enemies;

	//diamond
	std::vector<Diamond*> diamonds;

	//rocket
	std::vector<Rocket*> rockets;

	//collision
	std::vector<Collision*> collisions;

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
	
	//playerGUI
	sf::RectangleShape playerHp;
	sf::RectangleShape playerHpBack;	

	void initWindow();

	void initMusic();

	void initBackground();

	void initSystem();

	void initGUI();
public:
	Game();

	bool setGame();

	void updateWhilePlaying();
	
	bool running();

	void setUp();

	void reset();

	void run();

	void updatePollEvent();

	void updateKey();

	void updateGUI();

	void update();

	void updateBackground();
	
	void updateCollision();
	
	void updateEnemy();

	void updateDiamond();

	void updateRocket();

	void updateNewCollision();
	
	void render();

	void renderBackground();

	void renderGUI();
};
