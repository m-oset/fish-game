#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "Fish.hpp"
#include "Menu.hpp"

class Game {
private:
    sf::RenderWindow window;
    Player player;
    std::vector<Fish*> fish;
    
    sf::Texture background_texture, gameoverfish_texture;
    sf::Sprite background, gameoverfish;

    sf::Font font;
    sf::Text score_text;

    int default_mass = 500;
    int width = 1920, height = 1080;
    Menu menu;

    float last_spawn = 0, gameover_time = 0;
    void eat(Fish* fish);
    bool isPause = true;
    bool isGameOver = false;
    void gameOver();
    void startGame();
public:
    void start();
    void draw();
    void update(float diff);
    Game();
    ~Game();
};