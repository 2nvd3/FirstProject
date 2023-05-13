
#pragma once

#pragma warning(disable:4244)

#include "SFML/Graphics.hpp"
#include <vector>

class Background
{
private:
	sf::RenderWindow* window;

	class Layer
	{
	public:
		sf::Sprite sprite_array[2];

		float speed;
		float layer_pos_x[2];
	};

	std::vector<Layer> Layers;
	int layer_width;

public:
	void SetupBackground(sf::RenderWindow* window, std::vector<sf::Texture>& Textures, int layer_width);
	void MoveandDisplay();
};

std::vector<sf::Texture> TextureLayers(int typeOfBackground);
