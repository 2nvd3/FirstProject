#include "../Header/Character.h"

void Character::initTexture()
{
	this->texture.loadFromFile("Image/Character/bird.png");
}

void Character::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(1.3f,1.3f);
	this->sprite.setPosition(450, 450);
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

}

void Character::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Character::move(const float dirX, const float dirY)
{
	this->sprite.move(this->moveSpeed * dirX, this->moveSpeed * dirY);
}

Character::Character()
{
	this->hpMax = 400;
	this->hp = this->hpMax;
	this->moveSpeed = 4.f;
	this->initTexture();
	this->initSprite();
}

void Bird::initTexture()
{
	this->texture.loadFromFile("Image/Character/rio.png");
}

void Bird::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.5f, 0.5f);
	this->sprite.setPosition(250, 450);
}

const sf::FloatRect Bird::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Bird::getHp() const
{
	return this->hp;
}

const int& Bird::getHpMax() const
{
	return this->hpMax;
}

void Bird::setPos(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Bird::setPos(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Bird::buffHp(const int value)
{
	this->hp += value;
}

void Bird::setHp(const int hp)
{
	this->hp = hp;
}

void Bird::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) this->hp = 0;
}

void Bird::update()
{

}

void Bird::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Bird::move(const float dirX, const float dirY)
{
	this->sprite.move(this->moveSpeed * dirX, this->moveSpeed * dirY);
}

Bird::Bird()
{
	this->hpMax = 300;
	this->hp = this->hpMax;
	this->moveSpeed = 4.f;
	this->initTexture();
	this->initSprite();
}

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
