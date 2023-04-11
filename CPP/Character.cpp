#include "../Header/Character.h"

void Character::initTexture()
{
	this->texture.loadFromFile("Image/Character/bird.png");
}

void Character::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(1.3f,1.3f);
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

//display character
void Character::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

//control character
void Character::move(const float dirX, const float dirY)
{
	this->sprite.move(this->moveSpeed * dirX, this->moveSpeed * dirY);
}

Character::Character()
{
	this->hpMax = 400;
	this->hp = this->hpMax;
	this->moveSpeed = 3.f;
	this->initTexture();
	this->initSprite();
}
