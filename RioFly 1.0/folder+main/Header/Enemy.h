#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>

class Enemy
{
private:
	sf::Texture enemyTex;
	sf::Sprite enemySprite;

	int type;
	int hp;
	int hpMax;
	int	damage;
	int points;
	unsigned PointCount;
	void initTex();
	void initSprite();
	void initVari();

public:
	float speed;
	float posX;
	float posY;

	Enemy(float pos_x,float pos_y);

	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	void update();
	void render(sf::RenderTarget* target);
};
