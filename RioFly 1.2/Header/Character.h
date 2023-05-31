#pragma once

#pragma warning(disable : 4244)

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

#define PI 3.14159265

class Red
{
private:
	//Texture and Sprite
	sf::Texture texture;
	sf::Sprite sprite;

	//Variables
	float moveSpeed;
	float alpha = 0.f;
	float alphaMax = 28.f;
	float alphaSpeed = 2.2f;
	int hp;
	int hpMax;
	std::string link;

	//Animation
	sf::IntRect currentFrame;
	sf::Clock timer;

	//Private function
	void initSprite();
	void initAnimation();
public:
	bool alive = true;
	Red();
	void initTexture(std::string &link);

	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	float getPosX();
	float getPosY();

	void setPos(const sf::Vector2f pos);
	void setPos(const float x, const float y);
	
	void buffHp(const int value);
	void setHp(const int hp);
	void loseHp(const int value);

	void move(const float dirX,const float dirY);
	void updateMove();
	
	void update();
	void updateAnimation();

	void render(sf::RenderTarget* target);
};

class Rio
{
private:
	//Texture and sprite
	sf::Texture texture;
	sf::Sprite sprite;

	//animation
	sf::IntRect currentFrame;
	sf::Clock timer;
	
	//Variables
	std::string link;
	float alpha = 0.f;
	float alphaMax = 45.f;
	float alphaSpeed = 4.f;

	//private
	void initSprite();
	void initAnimation();
public:
	float speed = 30;
	bool alive = true;
	Rio();
	const sf::FloatRect getBounds() const;
	
	void initTexture(std::string& link);

	float getPosX();
	float getPosY();

	void setPos(const sf::Vector2f pos);
	void setPos(const float x, const float y);

	void move(const float dirX, const float dirY);
	void update();
	void updateAnimation();
	void updateMove();
	void render(sf::RenderTarget* target);
};

class Enemy
{
private:
	//texture
	sf::Texture enemyTex;
	sf::Sprite enemySprite;

	//animation
	sf::IntRect currentFrame;
	sf::Clock timer;

	//variables
	int	damage;

	std::string link;
	float speed;
	float posX;
	float posY;

	//private func
	void initSprite();
	void initVari();
	void initAnimation();
public:
	Enemy(float pos_x, float pos_y);

	const sf::FloatRect getBounds() const;
	const int& getDamage() const;
	
	void initTex(std::string& link);

	float getPosX();
	float getPosY();

	void update();
	void updateAnimation();
	void render(sf::RenderTarget& target);
};

class Diamond
{
private:
	//texture
	sf::Texture diamondTex;
	sf::Sprite diamondSprite;

	//animation
	sf::IntRect currentFrame;
	sf::Clock timer;

	//variables
	int points;
	unsigned PointCount;
	float speed;
	float posX;
	float posY;

	//private function
	void initTex();
	void initSprite();
	void initVari();
	void initAnimation();
public:
	Diamond(float pos_x, float pos_y);

	const sf::FloatRect getBounds() const;

	const int& getPoints() const;

	float getPosX();
	float getPosY();

	void update();
	void updateAnimation();
	void render(sf::RenderTarget& target);
};

class Rocket
{
private:
	//texture
	sf::Texture rocketTex;
	sf::Sprite rocketSprite;

	//animation
	sf::IntRect currentFrame;
	sf::Clock timer;

	//variables
	int	damage;
	float speed;
	float posX;
	float posY;

	float alpha = 0;
	float alphaSpeed = 4;

	//private function
	void initTex();
	void initSprite();
	void initVari();
	void initAnimation();
public:
	Rocket(float pos_x, float pos_y);

	const sf::FloatRect getBounds() const;

	const int& getDamage() const;

	float getPosX();
	float getPosY();

	void update(float rioPosX, float rioPosY, bool rioAlive);
	void updateAnimation();
	void render(sf::RenderTarget& target);

	void Catch(float rioPosX, float rioPosY, bool rioAlive);
};

class CollisionDiamond
{
private:
	//texture
	sf::Texture collisionTex;
	sf::Sprite collisionSprite;

	//animation
	sf::IntRect currentFrame;
	sf::Clock timer;

	//variables
	float posX;
	float posY;

	//private function
	void initTex();
	void initSprite();
	void initAnimation();
public:
	CollisionDiamond(float pos_x, float pos_y);

	void update();
	void updateAnimation();
	void render(sf::RenderTarget& target);
	bool renderer(sf::RenderTarget& target);
};

class CollisionEnemy
{
private:
	//texture
	sf::Texture collisionTex;
	sf::Sprite collisionSprite;

	//animation
	sf::IntRect currentFrame;
	sf::Clock timer;

	//variables
	float posX;
	float posY;

	//private function
	void initTex();
	void initSprite();
	void initAnimation();
public:
	CollisionEnemy(float pos_x, float pos_y);

	void update();
	void updateAnimation();
	void render(sf::RenderTarget& target);
};

bool collision(float posX_1, float posY_1, float scale_1, float width_1, float height_1, float posX_2, float posY_2, float scale_2, float width_2, float height_2);
