#include "../Header/Screen.h"

float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

//Tạo màn hình bắt đầu và các nút chức năng 
int gameStart(sf::RenderWindow* window, sf::Texture& play_choose_button, sf::Texture& play_unchoose_button,
    sf::Event* e, sf::Texture& begin_scr, sf::Music* music, sf::Texture& music_on_button, sf::Texture& music_off_button,
    sf::Texture& exit_on_button, sf::Texture& exit_off_button, bool& music_on)
{
    //Tạo hình vẽ
    sf::Sprite begin_screen(begin_scr);
    sf::Sprite play_button(play_unchoose_button);
    sf::Sprite exit_button(exit_off_button);
    sf::Sprite music_button(music_on_button);

    //Setup vị trí cho các nút chức năng
    sf::Vector2f button_pos = sf::Vector2f(1920 / 2 - 100, 1000 / 2 - 150);
    sf::Vector2f music_button_pos = sf::Vector2f(button_pos.x - 180, button_pos.y + 50);
    sf::Vector2f exit_button_pos = sf::Vector2f(button_pos.x + 225, button_pos.y + 56);

    //vị trí của chuột
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);

    //Bán kính của các nút chức năng
    float Button_Radius = 95;
    float Music_Radius = 60;
    float Exit_Radius = 65;

    //vị trí của chuột tới các nút chức năng
    float mouse_to_play_button = distance(button_pos.x + 100, button_pos.y + 100, mouse_pos.x, mouse_pos.y);
    float mouse_to_music_button = distance(music_button_pos.x + 85, music_button_pos.y + 65, mouse_pos.x, mouse_pos.y);
    float mouse_to_exit_button = distance(exit_button_pos.x + 60, exit_button_pos.y + 60, mouse_pos.x, mouse_pos.y);

    //dựng tỉ lệ
    begin_screen.setScale(1.f, 1.f);

    //play_button_setup
    play_button.setOrigin(0, 0);
    play_button.setScale(2, 2);
    play_button.setPosition(button_pos);

    //music_button_setup
    music_button.setOrigin(0, 0);
    music_button.setScale(0.5, 0.5);
    music_button.setPosition(music_button_pos);

    //exit_button_setup
    exit_button.setOrigin(0, 0);
    exit_button.setScale(1.25, 1.25);
    exit_button.setPosition(exit_button_pos);

    while (window->pollEvent(*e))
    {
        if (e->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return 2;
    }

    if (mouse_to_play_button <= Button_Radius)
    {
        play_button.setTexture(play_choose_button);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            return 1;
        }
    }

    if (music_on == true) music_button.setTexture(music_on_button);
    else music_button.setTexture(music_off_button);

    //Chức năng bật/tắt nhạc
    if (mouse_to_music_button <= Music_Radius)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!music_on)
            {
                music_on = true;
                music->play();
            }
            else
            {
                music_on = false;
                music->pause();
            }
        }
    }

    //Thoát game
    if (mouse_to_exit_button <= Exit_Radius)
    {
        exit_button.setTexture(exit_on_button);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return 2; //trả về 2 = thoát game
    }

    window->clear();
    window->draw(begin_screen);
    window->draw(play_button);
    window->draw(exit_button);
    window->draw(music_button);
    window->display();
    return 0;
}

//Tạo màn hình kết thúc và nút chơi lại
int gameReplay(sf::RenderWindow* window, sf::Texture& replay_choose_button, sf::Texture& replay_unchoose_button,
    sf::Event* e, sf::Texture& end_scr, int point, float text_pos_x, float text_pos_y, sf::Font& font)
{
    sf::Sprite replay_button(replay_unchoose_button);
    sf::Sprite screenEnd(end_scr);
    sf::Text text;

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
    sf::Vector2f replay_button_pos = sf::Vector2f(1920 / 2 - 100, 1000 / 2 + 100);

    std::string point_String = std::to_string(point);

    //bán kính nút chơi lại
    float Replay_Radius = 95;
    float mouse_to_replay_button = distance(replay_button_pos.x + 100, replay_button_pos.y + 100, mouse_pos.x, mouse_pos.y);

    //tỉ lệ màn hình kết thúc
    screenEnd.setScale(1.f, 1.f);

    //replay_button_setup
    replay_button.setOrigin(0, 0);
    replay_button.setScale(2, 2);
    replay_button.setPosition(replay_button_pos);

    //text_setup, font chữ
    text.setFont(font);
    text.setString(point_String);
    text.setCharacterSize(200);
    text.setFillColor(sf::Color::Black);
    text.setPosition(text_pos_x, text_pos_y);
    text.setStyle(sf::Text::Bold);

    if (mouse_to_replay_button <= Replay_Radius)
    {
        replay_button.setTexture(replay_choose_button);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            return 1; //trả về 1 = chơi lại
        }
    }

    while (window->pollEvent(*e))
    {
        if (e->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window->close();
            return 2; //trả về 2 = thoát game
        }
    }

    window->clear();
    window->draw(screenEnd);
    window->draw(text);
    window->draw(replay_button);
    window->display();
    return 0;
}

int Plots(sf::RenderWindow* window, sf::Event* e, sf::Texture& content, sf::Texture& tutorial,
    Red* red, Rio* rio, Background* background, sf::Texture& next_choose_button,
    sf::Texture& next_unchoose_button, bool& in_content, sf::Vector2f& but_pos)
{
    sf::Sprite sprite;
    sf::Sprite next_button(next_unchoose_button);

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
    sf::Vector2f next_button_pos = but_pos;

    if (in_content) sprite.setTexture(content);
    else sprite.setTexture(tutorial);

    //tỉ lệ hình vẽ
    sprite.setScale(1.f, 1.f);

    while (window->pollEvent(*e)) {
        if (e->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return 2; //trả về 2 = thoát game
    }

    next_button.setOrigin(0, 0);
    next_button.setPosition(next_button_pos);

    float next_button_radius = 50;
    float mouse_to_next_button = distance(next_button_pos.x + 50, next_button_pos.y + 50, mouse_pos.x, mouse_pos.y);

    if (mouse_to_next_button <= next_button_radius)
    {
        next_button.setTexture(next_choose_button);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (in_content)
            {
                in_content = false;
                but_pos = sf::Vector2f(1700, 1000 - 1000 / 6);
            }
            else return 1;
        }
    }

    background->MoveandDisplay();
    
    red->update();
    red->render(window);

    rio->update();
    rio->render(window);

    window->draw(sprite);
    window->draw(next_button);
    window->display();

    return 0;
}
