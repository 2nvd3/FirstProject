#include "../Header/Character.h"

//Character
void Character::initTexture(std::string& link)
{
	this->texture.loadFromFile(link);
	this->texture.setSmooth(true);
}

void Character::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, 63.285, 55);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.scale(1.8f, 1.8f);
	this->sprite.setPosition(320, 450);
	this->sprite.setOrigin(31.6425f, 27.5f);
}

void Character::initAnimation()
{
	this->timer.restart();
}

const sf::FloatRect Character::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Character::getHp() const
{
	return this->hp;
}

const int& Character::getHpMax() const
{
	return this->hpMax;
}

float Character::getPosX()
{
	return this->sprite.getPosition().x;
}

float Character::getPosY()
{
	return this->sprite.getPosition().y;
}

void Character::setPos(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Character::setPos(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Character::buffHp(const int value)
{
	this->hp += value;
}

void Character::setHp(const int hp)
{
	this->hp = hp;
}

void Character::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) this->hp = 0;
}

void Character::update()
{
	this->updateMove();
	this->updateAnimation();
}

void Character::updateAnimation()
{
	if (this->timer.getElapsedTime().asSeconds() >= 0.09f)
	{
		this->currentFrame.left += 63.f;
		if (this->currentFrame.left >= 379.7f)
		{
			this->currentFrame.left = 0;
		}
		this->timer.restart();
		this->sprite.setTextureRect(this->currentFrame);
	}
}

void Character::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Character::updateMove()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->sprite.move(-this->moveSpeed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->sprite.move(this->moveSpeed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->sprite.move(0.f, -this->moveSpeed);
		if (alpha > -alphaMax) alpha -= alphaSpeed;
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->sprite.move(0.f, this->moveSpeed);
			if (alpha < alphaMax) alpha += alphaSpeed;
		}
		else
		{
			if (alpha > 0) alpha -= alphaSpeed;
			if (alpha < 0) alpha += alphaSpeed;
		}
	}
	this->sprite.setRotation(alpha);
}

void Character::move(const float dirX, const float dirY)
{
	this->sprite.move(this->moveSpeed * dirX, this->moveSpeed * dirY);
}

Character::Character()
{
	this->hpMax = 300;
	this->hp = this->hpMax;
	this->moveSpeed = 8.f;
	this->initTexture(link);
	this->initSprite();
	this->initAnimation();
}

//Bird
void Bird::initTexture(std::string &link)
{
	this->texture.loadFromFile(link);
	this->texture.setSmooth(true);
}

float Bird::getPosX()
{
	return this->sprite.getPosition().x;
}

float Bird::getPosY()
{
	return this->sprite.getPosition().y;
}

void Bird::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, 191, 140);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setOrigin(95.5f, 70.f);
	this->sprite.scale(0.5f, 0.5f);
	this->sprite.setPosition(100, 450);
}

void Bird::initAnimation()
{
	this->timer.restart();
}

const sf::FloatRect Bird::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Bird::setPos(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Bird::setPos(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Bird::update()
{
	this->updateMove();
	this->updateAnimation();
}

void Bird::updateMove()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->sprite.move(-7.5f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->sprite.move(6.5f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->sprite.move(0.f, -6.5f);
		if (alpha > -alphaMax) alpha -= alphaSpeed;
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->sprite.move(0.f, 6.5f);
			if (alpha < alphaMax) alpha += alphaSpeed;
		}
		else {
			if (alpha > 0) alpha -= alphaSpeed;
			if (alpha < 0) alpha += alphaSpeed;
		}
	}
	this->sprite.setRotation(alpha);
}

void Bird::updateAnimation()
{
	if (this->timer.getElapsedTime().asSeconds() >= 0.12f)
	{
		this->currentFrame.left += 197.f;
		if (this->currentFrame.left >= 1578.f)
		{
			this->currentFrame.left = 0;

		}
		this->timer.restart();
		this->sprite.setTextureRect(this->currentFrame);
	}
}

void Bird::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Bird::move(const float dirX, const float dirY)
{
	this->sprite.move(this->speed * dirX, this->speed * dirY);
}

Bird::Bird()
{
	this->speed = 4;
	this->initTexture(this->link);
	this->initSprite();
	this->initAnimation();
}

//Enemy
void Enemy::initTex(std::string& link)
{	
	this->enemyTex.loadFromFile(link);
	this->enemyTex.setSmooth(true);
}

float Enemy::getPosX()
{
	return this->enemySprite.getPosition().x;
}

float Enemy::getPosY()
{
	return this->enemySprite.getPosition().y;
}

void Enemy::initVari()
{
	this->speed = rand() % 6 + 3;
	this->currentFrame = sf::IntRect(0, 0, 59, 54);
	this->damage = rand() % 50 + 25;
}

void Enemy::initAnimation()
{
	this->timer.restart();
}

void Enemy::initSprite()
{
	this->enemySprite.setTexture(this->enemyTex);
	this->enemySprite.setTextureRect(this->currentFrame);
	this->enemySprite.setScale(1.45f, 1.45f);
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->enemySprite.getGlobalBounds();
}

void Enemy::update()
{
	this->enemySprite.move(-this->speed, 0);
	this->updateAnimation();
}

void Enemy::updateAnimation()
{
	if (this->timer.getElapsedTime().asSeconds() >= 0.13f)
	{
			this->currentFrame.left += 56.99999805f;
			if (this->currentFrame.left >= 413.f)
			{
				this->currentFrame.left = 0;
			}
		this->timer.restart();
		this->enemySprite.setTextureRect(this->currentFrame);
	}
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->enemySprite);
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initTex(this->link);
	this->initSprite();
	this->initVari();
	this->initAnimation();
	this->enemySprite.setPosition(pos_x, pos_y);
}

//Diamond
void Diamond::initTex()
{
	this->diamondTex.loadFromFile("Image/Character/dias.png");
	this->currentFrame = sf::IntRect(0, 0, 88.125, 61);
	this->diamondTex.setSmooth(true);
}

void Diamond::initVari()
{
	this->PointCount = rand() % 40 + 25;
	this->speed = rand() % 5 + 3;
	this->points = this->PointCount;
}

void Diamond::initAnimation()
{
	this->timer.restart();
}

void Diamond::initSprite()
{
	this->diamondSprite.setTexture(this->diamondTex);
	this->diamondSprite.setTextureRect(this->currentFrame);
	this->diamondSprite.setScale(0.9f,0.9f);
}

const sf::FloatRect Diamond::getBounds() const
{
	return this->diamondSprite.getGlobalBounds();
}

void Diamond::update()
{
	this->diamondSprite.move(-this->speed, 0);
	this->updateAnimation();
}

void Diamond::updateAnimation()
{
	if (this->timer.getElapsedTime().asSeconds() >= 0.13f)
	{
		this->currentFrame.left += 88.125f;
		if (this->currentFrame.left >= 616.875f)
		{
			this->currentFrame.left = 0;
		}
		this->timer.restart();
		this->diamondSprite.setTextureRect(this->currentFrame);
	}
}

void Diamond::render(sf::RenderTarget& target)
{
	target.draw(this->diamondSprite);
}

const int& Diamond::getPoints() const
{
	return this->points;
}

float Diamond::getPosX()
{
	return this->diamondSprite.getPosition().x;
}

float Diamond::getPosY()
{
	return this->diamondSprite.getPosition().y;
}

Diamond::Diamond(float pos_x, float pos_y)
{
	this->initTex();
	this->initSprite();
	this->initVari();
	this->initAnimation();
	this->diamondSprite.setPosition(pos_x, pos_y);
}

//Rocket
void Rocket::initTex()
{
	this->rocketTex.loadFromFile("Image/Character/rocket.png");
	this->currentFrame = sf::IntRect(0, 0, 161, 65);
	this->rocketTex.setSmooth(true);
}

void Rocket::initSprite()
{
	this->rocketSprite.setTexture(this->rocketTex);
	this->rocketSprite.setTextureRect(this->currentFrame);
	this->rocketTex.setSmooth(true);
}

void Rocket::initVari()
{
	this->speed = 16;
	this->damage = 80;
}

void Rocket::initAnimation()
{
	this->timer.restart();
}

Rocket::Rocket(float pos_x, float pos_y)
{
	this->initTex();
	this->initSprite();
	this->initVari();
	this->initAnimation();
	this->rocketSprite.setScale(1.35f, 1.35f);
	this->rocketSprite.setPosition(pos_x, pos_y);
}

const sf::FloatRect Rocket::getBounds() const
{
	return this->rocketSprite.getGlobalBounds();
}

const int& Rocket::getDamage() const
{
	return this->damage;
}

float Rocket::getPosX()
{
	return this->rocketSprite.getPosition().x;
}

float Rocket::getPosY()
{
	return this->rocketSprite.getPosition().y;
}

void Rocket::updateAnimation()
{
	if (this->timer.getElapsedTime().asSeconds() >= 0.12f)
	{
		this->currentFrame.left += 161.f;
		if (this->currentFrame.left >= 495.f)
		{
			this->currentFrame.left = 0;
		}
		this->timer.restart();
		this->rocketSprite.setTextureRect(this->currentFrame);
	}
}

void Rocket::render(sf::RenderTarget& target)
{
	target.draw(this->rocketSprite);
}

void Rocket::Catch(float birdPosX, float birdPosY, bool birdAlive)
{
	this->posY = this->getPosY();
	this->posX = this->getPosX();
	int alpha_Second_Rocket = atan(abs(this->posY - birdPosY) / abs(this->posX - birdPosX)) * 180 / PI;
	if (abs(birdPosY - this->posY) > 0 && birdPosY > this->posY && birdAlive && birdPosX <= this->posX)
	{
		alpha_Second_Rocket = -(alpha_Second_Rocket);
		if (alpha > alpha_Second_Rocket) alpha -= alphaSpeed;
		else if (alpha < alpha_Second_Rocket) alpha += alphaSpeed;
	}
	else {
		if (abs(birdPosY - this->posY) > 10 && birdPosY < this->posY && birdAlive && birdPosX <= this->posX)
		{
			if (alpha > alpha_Second_Rocket) alpha -= alphaSpeed;
			else if (alpha < alpha_Second_Rocket) alpha += alphaSpeed;
		}
	}
	this->rocketSprite.setRotation(alpha);
}

void Rocket::update(float birdPosX, float birdPosY, bool birdAlive)
{
	Catch(birdPosX, birdPosY, birdAlive);
	if (alpha > 0) {
		this->rocketSprite.move(-this->speed, rand() % 4 - 5);
	}
	else this->rocketSprite.move(-this->speed, rand() % 5);
	this->updateAnimation();
}

//Collision with diamond
void CollisionDiamond::initTex()
{
	this->collisionTex.loadFromFile("Image/Character/diamondcollision.png");
	this->currentFrame = sf::IntRect(0, 0, 64, 64);
	this->collisionTex.setSmooth(true);
}

void CollisionDiamond::initAnimation()
{
	this->timer.restart();
}

void CollisionDiamond::initSprite()
{
	this->collisionSprite.setTexture(this->collisionTex);
	this->collisionSprite.setTextureRect(this->currentFrame);
	this->collisionSprite.setScale(2.f, 2.f);
}

void CollisionDiamond::update()
{
	this->updateAnimation();
}

void CollisionDiamond::updateAnimation()
{
	if (this->timer.getElapsedTime().asSeconds() >= 0.02f)
	{
		this->currentFrame.left += 64.f;
		this->timer.restart();
		this->collisionSprite.setTextureRect(this->currentFrame);
	}
}

void CollisionDiamond::render(sf::RenderTarget& target)
{
	target.draw(this->collisionSprite);
}

bool CollisionDiamond::renderer(sf::RenderTarget& target)
{
	target.draw(this->collisionSprite);
	if (this->currentFrame.left == 960) return true;
	return false;
}

CollisionDiamond::CollisionDiamond(float pos_x, float pos_y)
{
	this->initTex();
	this->initSprite();
	this->initAnimation();
	this->collisionSprite.setPosition(pos_x, pos_y);
}

//Collision with enemy
void CollisionEnemy::initTex()
{
	this->collisionTex.loadFromFile("Image/Character/enemycollision.png");
	this->currentFrame = sf::IntRect(0, 0, 64, 64);
	this->collisionTex.setSmooth(true);
}

void CollisionEnemy::initAnimation()
{
	this->timer.restart();
}

void CollisionEnemy::initSprite()
{
	this->collisionSprite.setTexture(this->collisionTex);
	this->collisionSprite.setTextureRect(this->currentFrame);
	this->collisionSprite.setScale(2.f, 2.f);
}

void CollisionEnemy::update()
{
	this->updateAnimation();
}

void CollisionEnemy::updateAnimation()
{
	if (this->timer.getElapsedTime().asSeconds() >= 0.02f)
	{
		this->currentFrame.left += 64.f;
		this->timer.restart();
		this->collisionSprite.setTextureRect(this->currentFrame);
	}
}

void CollisionEnemy::render(sf::RenderTarget& target)
{
	target.draw(this->collisionSprite);
}

CollisionEnemy::CollisionEnemy(float pos_x, float pos_y)
{
	this->initTex();
	this->initSprite();
	this->initAnimation();
	this->collisionSprite.setPosition(pos_x, pos_y);
}

bool collision(float posX_1, float posY_1, float scale_1, float width_1, float height_1, float posX_2, float posY_2, float scale_2, float width_2, float height_2)
{
	sf::Vector2f _First_tl = sf::Vector2f(posX_1 - (width_1 / 2) * scale_1, posY_1 - (height_1 / 2) * scale_1),
		_First_br = sf::Vector2f(posX_1 + (width_1 / 2) * scale_1, posY_1 + (height_1 / 2) * scale_1);

	sf::Vector2f _Second_tl = sf::Vector2f(posX_2 - (width_2 / 2) * scale_2, posY_2 - (height_2 / 2) * scale_2),
		_Second_br = sf::Vector2f(posX_2 + (width_2 / 2) * scale_2, posY_2 + (height_2 / 2) * scale_2);

	if (_First_br.x < _Second_tl.x || _First_tl.x > _Second_br.x) return false;
	if (_First_br.y < _Second_tl.y || _First_tl.y > _Second_br.y) return false;

	return true;
}
