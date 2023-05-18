#include "../Header/Utils.h"

//Run Game
void Game::updateGUI()
{
	//Setup GUI
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

	//Point
	std::stringstream ss;
	ss << this->points;
	this->pointTex.setString(ss.str());

	//Red's HP count
	std::stringstream sss;
	sss << "Health: " << character.getHp();
	this->playerHpTex.setString(sss.str());

	//Red's HP GUI
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
		i--;
	}
}

void Game::updateRocket()
{
	//Spawning rocket
	if (rand() % 400 == 0)
	{
		rockets.push_back(new Rocket(WINDOW_WIDTH + 20, rand() % window.getSize().y));
	}

	//Update
	int i = rockets.size() - 1;
	while (i >= 0)
	{
		rockets[i]->update(bird.getPosX(), bird.getPosY(), bird.alive);
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
		i--;
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
		//delete diamond
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
		i--;
	}
}

void Game::updateNewCollision()
{
	//Rio with diamond
	int dia_size = diamonds.size();
	for (int i = 0; i < dia_size; i++)
	{
		if (collision(bird.getPosX(), bird.getPosY(), 0.5, 161, 100, diamonds[i]->getPosX(),
			diamonds[i]->getPosY(), 0.9, 88, 61))
		{
			coldiamond.push_back(new CollisionDiamond(bird.getPosX(), bird.getPosY()-50));
		}
	}
	//update
	int dia_colli_size = coldiamond.size()-1;
	while (dia_colli_size >= 0)
	{
		coldiamond[dia_colli_size]->update();
		dia_colli_size--;
	}
	
	//Red with enemy
	int enemy_size = enemies.size();
	for (int i = 0; i < enemy_size; i++)
	{
		if (collision(character.getPosX(), character.getPosY(), 1.8, 64, 55, enemies[i]->getPosX(),
			enemies[i]->getPosY(), 1.45, 59, 54))
		{
			colenemy.push_back(new CollisionEnemy(character.getPosX(), character.getPosY()-50));
		}
	}
	//update
	int enemy_colli_size = colenemy.size()-1;
	while (enemy_colli_size >= 0)
	{
		colenemy[enemy_colli_size]->update();
		enemy_colli_size--;
	}
}

void Game::updateCollision()
{
	/////////Red collision with screen
	//left
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

	///////////Rio collision with screen
	//left
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
	//Set font
	font.loadFromFile("Font/FONT.ttf");

	//Setup music
	typeOfMusic = rand() % 10;
	Name_Of_Songs = SetMusics();
	Music.openFromFile(Name_Of_Songs[typeOfMusic]);
	Music.setLoop(true);
	Music.play();
	music_on = true;

	//Setup window
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::None);
	window.setFramerateLimit(FRAMES);
	window.setVerticalSyncEnabled(false);

	//Setup background
	typeOfBackground = rand() % 4;
	Texture_Layers = TextureLayers(typeOfBackground);
	background.SetupBackground(&window, Texture_Layers, 1920);

	//Setup screen
	begin_scr.loadFromFile("Image/Screen/screen_begin.png");
	end_scr.loadFromFile("Image/Screen/screen_end.png");
	choose_button.loadFromFile("Image/Screen/play_choosen.png");
	unchoose_button.loadFromFile("Image/Screen/play_unchoose.png");
	replay_choose_button.loadFromFile("Image/Screen/replay_choosen.png");
	replay_unchoose_button.loadFromFile("Image/Screen/replay_unchoose.png");
	music_on_button.loadFromFile("Image/Screen/music_on.png");
	music_off_button.loadFromFile("Image/Screen/music_off.png");
	exit_on_button.loadFromFile("Image/Screen/exit_on.png");
	exit_off_button.loadFromFile("Image/Screen/exit_off.png");
	content.loadFromFile("Image/Screen/content_screen.png");
	tutorial.loadFromFile("Image/Screen/tutor_screen.png");
	next_choose_button.loadFromFile("Image/Screen/next_choosen.png");
	next_unchoose_button.loadFromFile("Image/Screen/next_unchoose.png");
	pausing_scr.loadFromFile("Image/Screen/pausing_screen.png");
	sprite_pausing_screen.setTexture(pausing_scr);

	//Set texture smooth
	begin_scr.setSmooth(true);
	end_scr.setSmooth(true);
	choose_button.setSmooth(true);
	unchoose_button.setSmooth(true);
	replay_choose_button.setSmooth(true);
	replay_unchoose_button.setSmooth(true);
	music_on_button.setSmooth(true);
	music_off_button.setSmooth(true);
	exit_on_button.setSmooth(true);
	exit_off_button.setSmooth(true);
	content.setSmooth(true);
	tutorial.setSmooth(true);
	next_choose_button.setSmooth(true);
	next_unchoose_button.setSmooth(true);
	pausing_scr.setSmooth(true);

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
	
	//Setup characters
	bird.initTexture(linkrio);
	bird.setPos(130,450);

	character.initTexture(linkred);
	character.setPos(380, 450);

	//button
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
	in_content = true;

	//Clear
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
	for (auto* enemy : enemies) enemy->render(window);

	//Diamond Díplay
	for (auto* diamond : diamonds) diamond->render(window);

	//Display Rocket
	for (auto* rocket : rockets) rocket->render(this->window);

	//Display collision
	for(int i=0;i<coldiamond.size();i++)
	{
		if (coldiamond[i]->renderer(this->window)) {
			coldiamond.erase(coldiamond.begin() + i);
		}
	}

	for (auto* collision : colenemy) collision->render(this->window);

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

		while (gameStart(&window, choose_button, unchoose_button, &e, begin_scr,
			&Music, music_on_button, music_off_button, exit_on_button, exit_off_button, music_on) == 0)
		{
			//Frames Limit
			window.setFramerateLimit(FRAMES);
		}

		if (gameStart(&window, choose_button, unchoose_button, &e, begin_scr,
			&Music, music_on_button, music_off_button, exit_on_button, exit_off_button, music_on) == 2) return false;

		while (Contents_And_Tutor(&window, &e, content, tutorial, &character, &bird,
			&background, next_choose_button, next_unchoose_button, in_content, but_pos) == 0)
		{
			//Frames Limit
			window.setFramerateLimit(FRAMES);
		}

		if (Contents_And_Tutor(&window, &e, content, tutorial, &character, &bird,
			&background, next_choose_button, next_unchoose_button, in_content, but_pos) == 2) return false;

		while (bird.alive)
		{
			window.setFramerateLimit(FRAMES);

			window.pollEvent(e);
			if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				return false;
			}

			//Check in Screen
			if (e.type == sf::Event::LostFocus) in_screen = false;
			else if (e.type == sf::Event::GainedFocus) in_screen = true;

			//Loop In Game
			if (in_screen) updateWhilePlaying();
			else window.draw(sprite_pausing_screen);

			window.display();
		}

		std::string str_scr = std::to_string(points);
		int text_offset = -60 - 60 * (str_scr.length() - 1);

		while (gameReplay(&window, replay_choose_button, replay_unchoose_button, &e, end_scr, points,
			WINDOW_WIDTH / 2 + text_offset, WINDOW_HEIGHT / 2 - 165, font) == 0)
		{
			window.setFramerateLimit(FRAMES);
		}

		if (gameReplay(&window, replay_choose_button, replay_unchoose_button, &e, end_scr, points,
			WINDOW_WIDTH / 2 + text_offset, WINDOW_HEIGHT / 2 - 165, font) == 1) reset();

		if (gameReplay(&window, replay_choose_button, replay_unchoose_button, &e, end_scr, points,
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
