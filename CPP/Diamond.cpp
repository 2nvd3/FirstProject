#include "../Header/Diamond.h"

void Diamond::initTex()
{
	this->diamondTex.loadFromFile("Image/Character/diamond.png");
}

void Diamond::initVari()
{
	this->PointCount = rand() % 100 + 25;
	this->type = 0;
	this->speed = rand() % 5 + 1;
	this->hpMax = static_cast<float>(this->PointCount);
	this->hp = this->hpMax;
	this->damage = this->PointCount;
	this->points = this->PointCount;
}

void Diamond::initSprite()
{
	this->diamondSprite.setTexture(this->diamondTex);
}

const sf::FloatRect Diamond::getBounds() const
{
	return this->diamondSprite.getGlobalBounds();
}

void Diamond::update()
{
	this->diamondSprite.move(-this->speed, 0);
}

void Diamond::render(sf::RenderTarget* target)
{
	target->draw(this->diamondSprite);
}

const int& Diamond::getPoints() const
{
	// TODO: insert return statement here
	return this->points;
}

Diamond::Diamond(float pos_x, float pos_y)
{
	this->initTex();
	this->initSprite();
	this->initVari();
	this->diamondSprite.setPosition(pos_x, pos_y);
}
