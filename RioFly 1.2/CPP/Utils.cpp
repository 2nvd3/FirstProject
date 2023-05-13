#include "../Header/Utils.h"

//Run Game
void Game::updateGUI()
{
	this->pointTex.setFont(this->font);
	this->pointTex.setCharacterSize(100);
	this->pointTex.setOrigin(0.f, 0.f);
	this->pointTex.setPosition(sf::Vector2f(880.f, 160.f));
	this->pointTex.setFillColor(sf::Color::White);
	this->pointTex.setString("");

	this->playerHpTex.setFont(this->font);
	this->playerHpTex.setCharacterSize(30);
	this->playerHpTex.setOrigin(0.f, 0.f);
	this->playerHpTex.setPosition(sf::Vector2f(12.f, 900.f));
	if (this->character.getHp() <= 100) playerHpTex.setFillColor(sf::Color(253, 88, 88, 255));
	else this->playerHpTex.setFillColor(sf::Color::White);
	this->playerHpTex.setString("");

	this->playerHp.setSize(sf::Vector2f(200.f, 20.f));
	this->playerHp.setFillColor(sf::Color::Red);
	this->playerHp.setPosition(sf::Vector2f(12.f, 950.f));
	this->playerHpBack = this->playerHp;
	this->playerHpBack.setFillColor(sf::Color(25, 25, 25, 200));

	std::stringstream ss;
	ss << this->points;
	this->pointTex.setString(ss.str());

	std::stringstream sss;
	sss << "Health: " << character.getHp();
	this->playerHpTex.setString(sss.str());

	//updatePlayerGUI
	float HpPercent = static_cast<float> (character.getHp()) / character.getHpMax();
	this->playerHp.setSize(sf::Vector2f(200.f * HpPercent, this->playerHp.getSize().y));

}

void Game::updateEnemy()
{
	//Spawning enemies
	if (rand() % 55 == 0)
	{
		enemies.push_back(new Enemy(WINDOW_WIDTH + 20, rand() % window.getSize().y));
		for (int index = 0; index < enemies.size(); index++) enemies[index]->initTex(linkenemy);
	}

	//Update
	int i = enemies.size() - 1;
	while (i >= 0)
	{
		enemies[i]->update();
		//delete enemy
		if (enemies[i]->getBounds().left < -20)
		{
			enemies.erase(enemies.begin() + i);
		}
		else if (enemies[i]->getBounds().intersects(character.getBounds()))
		{
			if (character.alive)
			{
				character.loseHp(enemies[i]->getDamage());
				enemies.erase(enemies.begin() + i);
			}
		}
		else if (enemies[i]->getBounds().intersects(bird.getBounds()))
		{
			bird.alive = false;
		}
		i--; //move to previous element
	}
}

void Game::updateRocket()
{
	//Spawning rocket
	if (rand() % 300 == 0)
	{
		rockets.push_back(new Rocket(WINDOW_WIDTH + 20, rand() % window.getSize().y));
	}

	//Update
	int i = rockets.size() - 1;
	while (i >= 0)
	{
		rockets[i]->update(bird.getPosX(), bird.getPosY(), bird.speed, bird.alive);

		//delete rocket
		if (rockets[i]->getPosX() < -20)
		{
			this->rockets.erase(this->rockets.begin() + i);
		}
		else if (rockets[i]->getBounds().intersects(character.getBounds()))
		{
			if (character.alive)
			{
				character.loseHp(rockets[i]->getDamage());
				rockets.erase(rockets.begin() + i);
			}
		}
		else if (rockets[i]->getBounds().intersects(bird.getBounds()))
		{
			bird.alive = false;
		}
		i--; //move to previous element
	}
}

void Game::updateDiamond()
{
	//Spawning diamond
	if (rand() % 45 == 0)
	{
		diamonds.push_back(new Diamond(WINDOW_WIDTH + 20, rand() % window.getSize().y));
	}

	//update
	int i = diamonds.size() - 1;
	while (i >= 0)
	{
		diamonds[i]->update();
		//delete enemy
		if (diamonds[i]->getBounds().left < -20)
		{
			diamonds.erase(diamonds.begin() + i);
		}
		else if (diamonds[i]->getBounds().intersects(bird.getBounds()))
		{
			this->respawn += 1;
			this->points += diamonds[i]->getPoints();
			if (character.alive) character.buffHp(diamonds[i]->getPoints());
			diamonds.erase(diamonds.begin() + i);
		}
		i--; //move to previous element
	}
}

void Game::updateNewCollision()
{
	//Spawning diamond
	if (rand() % 85 == 0)
	{
		collisions.push_back(new Collision(WINDOW_WIDTH + 20, rand() % window.getSize().y));
	}

	//update
	int j = collisions.size() - 1;
	while (j >= 0)
	{
		collisions[j]->update();
		//delete enemy
		if (collisions[j]->getBounds().left < -20)
		{
			collisions.erase(collisions.begin() + j);
		}
		else if (collisions[j]->getBounds().intersects(bird.getBounds()))
		{
			collisions.erase(collisions.begin() + j);
		}
		j--; //move to previous element
	}
}

void Game::updateCollision()
{
	//left Character
	if (character.getBounds().left < 0.f)
	{
		character.setPos(62.f, character.getPosY());
	}
	//right
	else if (character.getBounds().left + character.getBounds().width > window.getSize().x)
	{
		character.setPos(window.getSize().x - 60.f, character.getPosY());
	}
	//top
	if (character.getBounds().top < 0.f)
	{
		character.setPos(character.getPosX(), window.getSize().y - 940.f);
	}
	//bottom	
	else if (character.getBounds().top + character.getBounds().height > window.getSize().y)
	{
		character.setPos(character.getPosX(), window.getSize().y - 60.f);
	}

	//left Bird
	if (bird.getBounds().left < 0.f)
	{
		bird.setPos(55.f, bird.getPosY());
	}
	//right
	else if (bird.getBounds().left + bird.getBounds().width > window.getSize().x)
	{
		bird.setPos(window.getSize().x - 60.f, bird.getPosY());
	}
	//top
	if (bird.getBounds().top < 0.f)
	{
		bird.setPos(bird.getPosX(), window.getSize().y - 940.f);
	}
	//bottom	
	else if (bird.getBounds().top + bird.getBounds().height > window.getSize().y)
	{
		bird.setPos(bird.getPosX(), window.getSize().y - 60.f);
	}
}

void Game::renderGUI()
{
	window.draw(this->playerHpTex);
	window.draw(this->pointTex);
	window.draw(this->playerHpBack);
	window.draw(this->playerHp);
}

void Game::setUp()
{
	//Load Font
	font.loadFromFile("Font/FONT.ttf");

	//Load Type of BG&M
	typeOfMusic = rand() % 10;
	typeOfBackground = rand() % 4;

	//Setup Music
	Name_Of_Songs = SetMusics();
	Music.openFromFile(Name_Of_Songs[typeOfMusic]);
	Music.setLoop(true);
	Music.play();
	Music_On = true;

	//Setup Window
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::None);
	window.setFramerateLimit(FRAMES);
	window.setVerticalSyncEnabled(false);

	//Setup BG
	Texture_Layers = TextureLayers(typeOfBackground);
	background.SetupBackground(&window, Texture_Layers, 1920);

	//Setup Screen
	textureScreenBegin.loadFromFile("Image/Screen/screen_begin.png");
	textureScreenEnd.loadFromFile("Image/Screen/screen_end.png");
	texture_play_choosen.loadFromFile("Image/Screen/play_choosen.png");
	texture_play_unchoose.loadFromFile("Image/Screen/play_unchoose.png");
	texture_replay_choosen.loadFromFile("Image/Screen/replay_choosen.png");
	texture_replay_unchoose.loadFromFile("Image/Screen/replay_unchoose.png");
	texture_music_on.loadFromFile("Image/Screen/music_on.png");
	texture_music_off.loadFromFile("Image/Screen/music_off.png");
	texture_exit_on.loadFromFile("Image/Screen/exit_on.png");
	texture_exit_off.loadFromFile("Image/Screen/exit_off.png");
	texture_contents.loadFromFile("Image/Screen/content_screen.png");
	texture_tutor.loadFromFile("Image/Screen/tutor_screen.png");
	texture_next_choosen.loadFromFile("Image/Screen/next_choosen.png");
	texture_next_unchoose.loadFromFile("Image/Screen/next_unchoose.png");
	texture_pausing_screen.loadFromFile("Image/Screen/pausing_screen.png");
	
	sprite_pausing_screen.setTexture(texture_pausing_screen);

	//Set Texture smooth
	textureScreenBegin.setSmooth(true);
	textureScreenEnd.setSmooth(true);
	texture_play_choosen.setSmooth(true);
	texture_play_unchoose.setSmooth(true);
	texture_replay_choosen.setSmooth(true);
	texture_replay_unchoose.setSmooth(true);
	texture_music_on.setSmooth(true);
	texture_music_off.setSmooth(true);
	texture_exit_on.setSmooth(true);
	texture_exit_off.setSmooth(true);
	texture_contents.setSmooth(true);
	texture_tutor.setSmooth(true);
	texture_next_choosen.setSmooth(true);
	texture_next_unchoose.setSmooth(true);
	texture_pausing_screen.setSmooth(true);

	//Setup Character
	if (typeOfBackground == 0 || typeOfBackground == 3)
	{
		this->linkrio = "Image/Character/rio1.png";
		this->linkred = "Image/Character/red1.png";
		this->linkenemy = "Image/Character/enemy1.png";
	}
	else {
		this->linkrio = "Image/Character/rio2.png";
		this->linkred = "Image/Character/red2.png";
		this->linkenemy = "Image/Character/enemy2.png";
	}

	bird.initTexture(linkrio);
	bird.setPos(130,450);

	character.initTexture(linkred);
	character.setPos(380, 450);

	//Pos
	but_pos = sf::Vector2f(100, 1000 - 1000 / 6);
}

void Game::reset()
{
	window.setFramerateLimit(FRAMES);
	bird.alive = true;
	character.alive = true;
	character.setHp(400);

	points = 0;
	but_pos = sf::Vector2f(100, 1000 - 1000 / 6);
	at_content = true;

	//Clear Vector
	Texture_Layers.clear();
	enemies.clear();
	diamonds.clear();

	setUp();
}

//Loop While Playing
void Game::updateWhilePlaying()
{
	//Character Control
	if (character.alive) character.update();
	bird.update();
	updateCollision();

	//Enemy Control
	updateEnemy();

	//Diamond Control
	updateDiamond();

	//Rocket Control
	updateRocket();

	//Collision control
	updateNewCollision();

	//Clear and Display Game
	window.clear(sf::Color(255, 255, 255, 255));
	background.MoveandDisplay();
	if (character.alive) character.render(&window);
	bird.render(&window);

	//Enemy Display
	for (auto* enemy : this->enemies) enemy->render(window);

	//Diamond Díplay
	for (auto* diamond : this->diamonds) diamond->render(window);

	//Display Rocket
	for (auto* rocket : this->rockets) rocket->render(this->window);

	//Display collision
	//for (auto *collision: this->collisions) collision->render(this->window);

	//Respawn Logic
	if (character.getHp() <= 0)
	{
		character.alive = false;
		character.setHp(0);
	}

	if (!character.alive) {
		if (respawn >= 7)
		{
			character.alive = true;
			character.setHp(400);
		}
	}
	else respawn = 0;

	//Display Score and Health
	updateGUI();
	renderGUI();
}

//Main Game Loop Everything
bool Game::setGame()
{
	setUp();
	while (window.isOpen())
	{
		//Frames Limit
		window.setFramerateLimit(FRAMES);

		while (gameStart(&window, texture_play_choosen, texture_play_unchoose, &e, textureScreenBegin,
			&Music, texture_music_on, texture_music_off, texture_exit_on, texture_exit_off, Music_On) == 0)
		{
			//Frames Limit
			window.setFramerateLimit(FRAMES);
		}

		if (gameStart(&window, texture_play_choosen, texture_play_unchoose, &e, textureScreenBegin,
			&Music, texture_music_on, texture_music_off, texture_exit_on, texture_exit_off, Music_On) == 2) return false;

		while (Contents_And_Tutor(&window, &e, texture_contents, texture_tutor, &character, &bird,
			&background, texture_next_choosen, texture_next_unchoose, at_content, but_pos) == 0)
		{
			// Frames Limit
			window.setFramerateLimit(FRAMES);
		}

		if (Contents_And_Tutor(&window, &e, texture_contents, texture_tutor, &character, &bird,
			&background, texture_next_choosen, texture_next_unchoose, at_content, but_pos) == 2) return false;

		while (bird.alive)
		{
			//Frames Limit
			window.setFramerateLimit(FRAMES);

			//Event's loop
			window.pollEvent(e);
			if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				return false;
			}

			//check in Game Screen
			if (e.type == sf::Event::LostFocus) inScreen = false;
			else if (e.type == sf::Event::GainedFocus) inScreen = true;

			//Loop In Game Screen
			if (inScreen) updateWhilePlaying();

			if (!inScreen) window.draw(sprite_pausing_screen);

			window.display();
		}

		std::string str_scr = std::to_string(points);
		int text_offset = -60 - 60 * (str_scr.length() - 1);

		while (gameReplay(&window, texture_replay_choosen, texture_replay_unchoose, &e, textureScreenEnd, points,
			WINDOW_WIDTH / 2 + text_offset, WINDOW_HEIGHT / 2 - 165, font) == 0)
		{
			window.setFramerateLimit(FRAMES); //Frames Limit
		}

		if (gameReplay(&window, texture_replay_choosen, texture_replay_unchoose, &e, textureScreenEnd, points,
			WINDOW_WIDTH / 2 + text_offset, WINDOW_HEIGHT / 2 - 165, font) == 1) reset();

		if (gameReplay(&window, texture_replay_choosen, texture_replay_unchoose, &e, textureScreenEnd, points,
			WINDOW_WIDTH / 2 + text_offset, WINDOW_HEIGHT / 2 - 165, font) == 2) return false;
	}
	return false;
}

//Game Run
bool Game::running()
{
	if (!setGame())
	{
		Music.stop();
		return EXIT_SUCCESS;
	}
	window.close();
	return EXIT_SUCCESS;
}

Game::Game()
{
	this->running();
}
