#include "../Header/Utils.h"

void Game::initWindow()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::None);
	window.setFramerateLimit(FRAMES);
	window.setVerticalSyncEnabled(false);
}

void Game::initScreen()
{
	this->texture_contents.loadFromFile("Image/Screen/Content.png");
	this->texture_tutor.loadFromFile("Image/Screen/Tutor.png");
	this->content.setTexture(this->texture_contents);
	this->tutor.setTexture(this->texture_tutor);
}

void Game::initBackground()
{
	this->typeOfBackground = rand() % 4;
	Texture_Layers = TextureLayers(typeOfBackground);
	background.SetupBackground(&window, Texture_Layers, 1919);
	//this->backgroundTex.loadFromFile("Image/Background.png");
	//this->background.setTexture(this->backgroundTex);
}

void Game::initSystem()
{
	this->points = 0;
}

void Game::initMusic()
{
	this->typeOfMusic = rand() % 11;
	Name_Of_Songs = SetMusics();
	if (!Music.openFromFile(Name_Of_Songs[typeOfMusic]))
	{
		std::cout << "Musicn't";
	}
	Music.setLoop(true);
}

void Game::initGUI()
{
	font.loadFromFile("Font/FONT.ttf");
	//init Point Text
	this->pointTex.setFont(this->font);
	this->pointTex.setCharacterSize(30);
	this->pointTex.setPosition(sf::Vector2f(10.f,5.f));
	this->pointTex.setFillColor(sf::Color::Red);
	//this->pointTex.setStyle(sf::Text::Bold);
	this->pointTex.setString("Game Over!");

	this->gameOverTex.setFont(this->font);
	this->gameOverTex.setCharacterSize(100);
	this->gameOverTex.setPosition(sf::Vector2f(10.f, 5.f));
	this->gameOverTex.setFillColor(sf::Color::Red);
	this->gameOverTex.setString("Game Over!");
	this->gameOverTex.setPosition(
		window.getSize().x / 2.f - this->gameOverTex.getGlobalBounds().width / 2.f,
		window.getSize().y / 2.f - this->gameOverTex.getGlobalBounds().height / 2.f - 80.f);

	//init playerGUI
	this->playerHp.setSize(sf::Vector2f(200.f, 20.f));
	this->playerHp.setFillColor(sf::Color::Red);
	this->playerHp.setPosition(sf::Vector2f(12.f, 40.f));
	this->playerHpBack = this->playerHp;
	this->playerHpBack.setFillColor(sf::Color(25, 25, 25, 200));

}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->pointTex.setString(ss.str());

	//updatePlayerGUI
	float HpPercent = static_cast<float> (character.getHp()) / character.getHpMax();
	this->playerHp.setSize(sf::Vector2f(200.f*HpPercent,this->playerHp.getSize().y));
}
		
void Game::updateEnemy()
{
	//Spawning enemies
	if (rand() % 55 == 0)
	{
		this->enemies.push_back(new Enemy(WINDOW_WIDTH, rand() % window.getSize().y));
		window.setFramerateLimit(FRAMES);
	}

	//Update
	unsigned counter = 0;
	for (auto *enemy: this->enemies)
	{
		enemy->update();
		//Delete enemies
		if (enemy->getBounds().left > window.getSize().x)
		{
			this->enemies.erase(this->enemies.begin() + counter);
			window.setFramerateLimit(FRAMES);
		}
		//enemy player collision
		else if (enemy->getBounds().intersects(character.getBounds()))
		{
			//delete this->enemies.at(counter);
			character.loseHp(this->enemies.at(counter)->getDamage());
			this->enemies.erase(this->enemies.begin() + counter);
			window.setFramerateLimit(FRAMES);
		}
		else if(enemy->getBounds().intersects(bird.getBounds()))
		{
			character.loseHp(1000);
		}

		++counter;
	}
}

void Game::updateDiamond()
{
	//Spawning diamond
	if (rand() % 45 == 0)
	{
		this->diamonds.push_back(new Diamond(WINDOW_WIDTH, rand() % window.getSize().y));
		window.setFramerateLimit(FRAMES);
	}

	//Update
	unsigned counter = 0;
	for (auto* diamond : this->diamonds)
	{
		diamond->update();
		//Delete diamond
		if (diamond->getBounds().left > window.getSize().x)
		{
			this->diamonds.erase(this->diamonds.begin() + counter);
			window.setFramerateLimit(FRAMES);
		}
		else if (diamond->getBounds().intersects(bird.getBounds()))
		{
			//delete this->enemies.at(counter);
			this->points += this->diamonds.at(counter)->getPoints();
			character.buffHp(this->diamonds.at(counter)->getPoints());
			this->diamonds.erase(this->diamonds.begin() + counter);
			window.setFramerateLimit(FRAMES);
		}

		++counter;
	}
}

void Game::updatePollEvent()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		switch (e.type)
		{
		//case sf::Event::LostFocus:
		//	window.pause();
		//case sf::Event::GainedFocus:
		//	window.resume();
		case sf::Event::Closed():
			window.close();
			break;
		case sf::Event::KeyPressed:
			switch (e.key.code) 
			{
			case sf::Keyboard::Escape:
				window.close();
				break;
			}
		}
	}
}

void Game::updateKey()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		character.move(-1.4f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		character.move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		character.move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		character.move(0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		bird.move(-1.4f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		bird.move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		bird.move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		bird.move(0.f, 1.f);
}

void Game::update()
{
	this->updateBackground();

	this->updateKey();

	character.update();

	this->updateCollision();

	this->updateEnemy();

	this->updateDiamond();

	this->updateGUI();
	if (character.getHp() <= 0) Music.pause();

}

void Game::updateBackground()
{
}

void Game::updateCollision()
{
	//left Character
	if (character.getBounds().left < 0.f)
	{
		character.setPos(0.f, character.getBounds().top);
	}
	//right
	else if (character.getBounds().left + character.getBounds().width > window.getSize().x)
	{
		character.setPos(window.getSize().x - character.getBounds().width , character.getBounds().top);
	}
	//top
	if (character.getBounds().top < 0.f)
	{
		character.setPos(character.getBounds().left, 0.f);
	}
	//bottom	
	else if (character.getBounds().top + character.getBounds().height > window.getSize().y)
	{
		character.setPos(character.getBounds().left, window.getSize().y - character.getBounds().height);
	}
	
	//left Bird
	if (bird.getBounds().left < 0.f)
	{
		bird.setPos(0.f, bird.getBounds().top);
	}
	//right
	else if (bird.getBounds().left + bird.getBounds().width > window.getSize().x)
	{
		bird.setPos(window.getSize().x - bird.getBounds().width, bird.getBounds().top);
	}
	//top
	if (bird.getBounds().top < 0.f)
	{
		bird.setPos(bird.getBounds().left, 0.f);
	}
	//bottom	
	else if (bird.getBounds().top + bird.getBounds().height > window.getSize().y)
	{
		bird.setPos(bird.getBounds().left, window.getSize().y - bird.getBounds().height);
	}
}

void Game::render()
{
	window.clear();

	window.draw(content);
	//window.draw(tutor);
	this->renderBackground();
	character.render(window);
	bird.render(window);

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
		window.setFramerateLimit(FRAMES);
	}
	
	for (auto* diamond : this->diamonds)
	{
		diamond->render(&window);
		window.setFramerateLimit(FRAMES);
	}

	this->renderGUI();

	if (character.getHp() <= 0) window.draw(this->gameOverTex);
		
	window.display();
}

void Game::renderBackground()
{
	background.MoveandDisplay();
}

void Game::renderGUI()
{
	window.draw(this->pointTex);
	window.draw(this->playerHpBack);
	window.draw(this->playerHp);
}

void Game::run()
{
	Music.play();
	while (window.isOpen())
	{
		this->updatePollEvent();
		if (character.getHp() > 0)
		{
			this->update();
			this->render();
		}
	}
}

Game::Game()
{
	this->initMusic();
	this->initWindow();
	this->initScreen();
	this->initBackground();
	this->initSystem();
	this->initGUI();
}
