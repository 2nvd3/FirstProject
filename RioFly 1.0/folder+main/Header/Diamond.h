#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>

class Diamond
{
private:
	sf::Texture diamondTex;
	sf::Sprite diamondSprite;

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

	Diamond(float pos_x, float pos_y);

	const sf::FloatRect getBounds() const;
	const int& getPoints() const;

	void update();
	void render(sf::RenderTarget* target);
};
