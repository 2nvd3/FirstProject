#pragma once

#pragma warning (disable : 4305)

#include <SFML/Audio.hpp>
#include "Character.h"
#include "Background.h"

float distance(float x1, float y1, float x2, float y2);

int gameStart(sf::RenderWindow* window, sf::Texture& play_choose_button, sf::Texture& play_unchoose_button,
    sf::Event* e, sf::Texture& begin_scr, sf::Music* music, sf::Texture& music_on_button, sf::Texture& music_off_button,
    sf::Texture& exit_on_button, sf::Texture& exit_off_button, bool& music_on);

int gameReplay(sf::RenderWindow* window, sf::Texture& replay_choose_button, sf::Texture& replay_unchoose_button,
    sf::Event* e, sf::Texture& end_scr, int point, float text_pos_x, float text_pos_y, sf::Font& font);

int Plots(sf::RenderWindow* window, sf::Event* e, sf::Texture& content, sf::Texture& tutorial,
    Red* red, Rio* rio, Background* background, sf::Texture& next_choose_button,
    sf::Texture& next_unchoose_button, bool& in_content, sf::Vector2f& but_pos);
