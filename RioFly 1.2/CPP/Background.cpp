#include "../Header/Background.h"

std::vector<sf::Texture> TextureLayers(int typeOfBackground)
{
	std::vector<sf::Texture> tex_vex;
	sf::Texture temp_Texture;

	if (typeOfBackground == 0)
	{
		temp_Texture.loadFromFile("Image/LayerBackground/0.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/1.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/2.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/3.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/4.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/5.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/6.png"); tex_vex.push_back(temp_Texture);
	}

	if (typeOfBackground == 1)
	{
		temp_Texture.loadFromFile("Image/LayerBackground/7.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/8.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/9.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/10.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/11.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/12.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/13.png"); tex_vex.push_back(temp_Texture);
	}

	if (typeOfBackground == 2)
	{
		temp_Texture.loadFromFile("Image/LayerBackground/14.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/15.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/16.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/17.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/18.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/19.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/20.png"); tex_vex.push_back(temp_Texture);
	}

	if (typeOfBackground == 3)
	{
		temp_Texture.loadFromFile("Image/LayerBackground/21.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/22.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/23.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/24.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/25.png"); tex_vex.push_back(temp_Texture);
		temp_Texture.loadFromFile("Image/LayerBackground/26.png"); tex_vex.push_back(temp_Texture);
	}
	temp_Texture.setSmooth(true);
	return tex_vex;
}

void Background::SetupBackground(sf::RenderWindow* window, std::vector<sf::Texture>& Textures, int layer_width)
{
	this->window = window;
	this->layer_width = layer_width;
	int n = Textures.size();
	for (int i = 0; i < n; i++)
	{
		Layer temp_Layer;
		sf::Sprite temp_sprite(Textures[i]);
		this->window->draw(temp_sprite);
		temp_Layer.speed = i * 0.3f;//Set layer move speed
		temp_Layer.layer_pos_x[0] = 0;
		temp_Layer.layer_pos_x[1] = this->layer_width;
		temp_Layer.sprite_array[0] = temp_Layer.sprite_array[1] = temp_sprite;
		this->Layers.push_back(temp_Layer);
	}
}

void Background::MoveandDisplay()
{
	int n = Layers.size();
	for (int i = 0; i < n; i++)
	{
		this->Layers[i].layer_pos_x[0] -= this->Layers[i].speed;
		this->Layers[i].layer_pos_x[1] -= this->Layers[i].speed;
		if (this->Layers[i].layer_pos_x[0] <= -this->layer_width) this->Layers[i].layer_pos_x[0] = this->layer_width;
		if (this->Layers[i].layer_pos_x[1] <= -this->layer_width) this->Layers[i].layer_pos_x[1] = this->layer_width;
		this->Layers[i].sprite_array[0].setPosition(Layers[i].layer_pos_x[0], 0);
		this->Layers[i].sprite_array[1].setPosition(Layers[i].layer_pos_x[1], 0);
		this->window->draw(Layers[i].sprite_array[0]);
		this->window->draw(Layers[i].sprite_array[1]);
	}
}
