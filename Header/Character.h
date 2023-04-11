#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Character
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float moveSpeed;

	int hp;
	int hpMax;
	//private funtion
	void initTexture();
	void initSprite();
public:
	Character();
	const sf::FloatRect getBounds() const;
	
	const int& getHp() const;
	const int& getHpMax() const;

	void setPos(const sf::Vector2f pos);
	void setPos(const float x, const float y);
	
	void buffHp(const int value);
	void setHp(const int hp);
	void loseHp(const int value);

	void move(const float dirX,const float dirY);
	void update();
	void render(sf::RenderTarget &target);
};
