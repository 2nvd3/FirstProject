#include "../Header/Enemy.h"

void Enemy::initTex()
{
	this->enemyTex.loadFromFile("Image/Character/enemy.png");
}

void Enemy::initVari()
{
	this->PointCount = rand() % 100 + 25;
	this->type = 0;
	this->speed = rand()%6+2.7;
	this->hpMax = static_cast<float>(this->PointCount);
	this->hp = this->hpMax;
	this->damage = this->PointCount;
	this->points = this->PointCount;
}

void Enemy::initSprite()
{
	this->enemySprite.setTexture(this->enemyTex);
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->enemySprite.getGlobalBounds();
}

void Enemy::update()
{
	this->enemySprite.move(-this->speed, 0);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->enemySprite);
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initTex();
	this->initSprite();
	this->initVari();
	this->enemySprite.setPosition(pos_x, pos_y);
}
