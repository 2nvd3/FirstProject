#include "../Header/Utils.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::None);
	this->window->setFramerateLimit(FRAMES);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initCharacter()
{
	this->character = new Character();
}

void Game::initEnemy()
{
	this->spawnTimerMax = 110.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initDiamond()
{
	this->spawnTimerMaxdiamond = 110.f;
	this->spawnTimerdiamond = this->spawnTimerMaxdiamond;
}

void Game::initBackground()
{
	this->backgroundTex.loadFromFile("Image/background.png");
	this->background.setTexture(this->backgroundTex);
}

void Game::initSystem()
{
	this->points = 0;
}

void Game::initGUI()
{
	font.loadFromFile("Font/FONT.ttf");
	//init Point Text
	this->pointTex.setFont(this->font);
	this->pointTex.setCharacterSize(30);
	this->pointTex.setPosition(sf::Vector2f(10.f,5.f));
	this->pointTex.setFillColor(sf::Color::Red);
	this->pointTex.setString("Game Over!");

	this->gameOverTex.setFont(this->font);
	this->gameOverTex.setCharacterSize(60);
	this->gameOverTex.setPosition(sf::Vector2f(10.f, 5.f));
	this->gameOverTex.setFillColor(sf::Color::Red);
	this->gameOverTex.setString("Game Over!");
	this->gameOverTex.setPosition(
		this->window->getSize().x / 2.f - this->gameOverTex.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverTex.getGlobalBounds().height / 2.f);

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
	float HpPercent = static_cast<float> (this->character->getHp()) / this->character->getHpMax();
	this->playerHp.setSize(sf::Vector2f(200.f*HpPercent,this->playerHp.getSize().y));
}
		
void Game::updateEnemy()
{
	//Spawning enemies
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(WINDOW_WIDTH, rand() % this->window->getSize().y));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto *enemy: this->enemies)
	{
		enemy->update();

		if (enemy->getBounds().left > this->window->getSize().x)
		{
			//Delete enemies
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//enemy player collision
		else if (enemy->getBounds().intersects(this->character->getBounds()))
		{
			//delete this->enemies.at(counter);
			this->character->loseHp(this->enemies.at(counter)->getDamage());
			this->enemies.erase(this->enemies.begin() + counter);
		}

		++counter;
	}
}

void Game::updateDiamond()
{
	//Spawning diamond
	this->spawnTimerdiamond += 0.5f;
	if (this->spawnTimerdiamond >= this->spawnTimerMaxdiamond)
	{
		this->diamonds.push_back(new Diamond(WINDOW_WIDTH, rand() % this->window->getSize().y));
		this->spawnTimerdiamond = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* diamond : this->diamonds)
	{
		diamond->update();

		if (diamond->getBounds().left > this->window->getSize().x)
		{
			//Delete diamond
			this->diamonds.erase(this->diamonds.begin() + counter);
		}
		else if (diamond->getBounds().intersects(this->character->getBounds()))
		{
			//delete this->enemies.at(counter);
			this->points += this->diamonds.at(counter)->getPoints();
			this->character->buffHp(this->diamonds.at(counter)->getPoints());
			this->diamonds.erase(this->diamonds.begin() + counter);
		}

		++counter;
	}
}

void Game::updatePollEvent()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed():
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			switch (e.key.code) 
			{
			case sf::Keyboard::Escape:
				this->window->close();
			}
		}
	}
}

void Game::updateKey()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->character->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->character->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->character->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->character->move(0.f, 1.f);
}

void Game::update()
{
	this->updateKey();

	this->character->update();

	this->updateCollision();

	this->updateEnemy();

	this->updateDiamond();

	this->updateGUI();
}

void Game::updateBackground()
{
}

void Game::updateCollision()
{
	//left
	if (this->character->getBounds().left < 0.f)
	{
		this->character->setPos(0.f, this->character->getBounds().top);
	}
	//right
	else if (this->character->getBounds().left + this->character->getBounds().width > this->window->getSize().x)
	{
		this->character->setPos(this->window->getSize().x - this->character->getBounds().width , this->character->getBounds().top);
	}
	//top
	if (this->character->getBounds().top < 0.f)
	{
		this->character->setPos(this->character->getBounds().left, 0.f);
	}
	//bottom	
	else if (this->character->getBounds().top + this->character->getBounds().height > this->window->getSize().y)
	{
		this->character->setPos(this->character->getBounds().left, this->window->getSize().y - this->character->getBounds().height);
	}
	
}

void Game::render()
{
	this->window->clear();

	this->renderBackground();

	this->character->render(*this->window);
	
	
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* diamond : this->diamonds)
	{
		diamond->render(this->window);
	}

	this->renderGUI();

	if (this->character->getHp() <= 0) this->window->draw(this->gameOverTex);

	this->window->display();
}

void Game::renderBackground()
{
	this->window->draw(this->background);
}

void Game::renderGUI()
{
	this->window->draw(this->pointTex);
	this->window->draw(this->playerHpBack);
	this->window->draw(this->playerHp);
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvent();
		if (this->character->getHp() > 0)
		{
			this->update();
			this->render();
		}
	}
}

Game::Game()
{
	this->initWindow();
	this->initCharacter();
	this->initBackground();
	this->initEnemy();
	this->initDiamond();
	this->initSystem();
	this->initGUI();
}
