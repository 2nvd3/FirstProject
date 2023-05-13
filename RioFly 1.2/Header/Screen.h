#pragma once

#pragma warning (disable : 4305)

#include <SFML/Audio.hpp>
#include "Character.h"
#include "Background.h"

float distance(float x1, float y1, float x2, float y2);

int gameStart(sf::RenderWindow* window, sf::Texture& texture_play_choosen, sf::Texture& texture_play_unchoose,
    sf::Event* e, sf::Texture& textureScreenBegin, sf::Music* music, sf::Texture& texture_music_on,
    sf::Texture& texture_music_off, sf::Texture& texture_exit_on, sf::Texture& texture_exit_off, bool& music_on);

int gameReplay(sf::RenderWindow* window, sf::Texture& texture_replay_choosen, sf::Texture& texture_replay_unchoose,
    sf::Event* e, sf::Texture& textureScreenEnd, int score, float text_Pos_X,
    float text_Pos_Y, sf::Font& font);

int Contents_And_Tutor(sf::RenderWindow* window, sf::Event* e, sf::Texture& texture_content,
    sf::Texture& texture_tutor, Character* character, Bird* bird,
    Background* background, sf::Texture& texture_next_choosen, sf::Texture& texture_next_unchoose,
    bool& at_contents, sf::Vector2f& pos_in);
