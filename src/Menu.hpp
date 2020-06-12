#pragma once
#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Texture play_texture, exit_texture, skin_texture;
    sf::Sprite play, exit, skin;


    sf::Font font;
    sf::Text score_text[10], leader;
public:
    void update(int width, int height);
    void draw(sf::RenderWindow & window);
    bool isPlayPressed(float x, float y);
    bool isExitPressed(float x, float y);
    bool isSkinChangePressed(float x, float y);
    Menu();
};