#include "Menu.hpp"
#include <iostream>
#include <fstream>


void Menu::update() {
    std::fstream file("wyniki.txt");
    for(int i = 0; i < 5; i++) {
        int x; file >> x;
        score_text[i].setString(std::to_string(x));
    }
}

void Menu::draw(sf::RenderWindow & window) {
    window.draw(play);
    window.draw(skin);
    window.draw(exit);
    for(int i = 0; i < 5; i++) {
        window.draw(score_text[i]);
    }
    window.draw(leader);
}

bool Menu::isPlayPressed(float x, float y) {
    return play.getGlobalBounds().contains({x, y});
}

bool Menu::isExitPressed(float x, float y) {
    return exit.getGlobalBounds().contains({x, y});
}

bool Menu::isSkinChangePressed(float x, float y) {
    return skin.getGlobalBounds().contains({x, y});
}

Menu::Menu() {
    play_texture.loadFromFile("img/playbutton.png");
    play.setTexture(play_texture);
    exit_texture.loadFromFile("img/exitbutton.png");
    exit.setTexture(exit_texture);
    skin_texture.loadFromFile("img/changeskinbutton.png");
    skin.setTexture(skin_texture);

    float X = 450.f, Y = 120.f;
    play.setScale({X / play_texture.getSize().x, Y / play_texture.getSize().y});
    exit.setScale({X / exit_texture.getSize().x, Y / exit_texture.getSize().y});
    skin.setScale({X / skin_texture.getSize().x, Y / skin_texture.getSize().y});

    float D = 150.f, S = 330.f + Y/2;
    play.setPosition(1920.0/2.0-X/2, S - Y/2);
    skin.setPosition(1920.0/2.0-X/2, S + D -Y/2);
    exit.setPosition(1920.0/2.0-X/2, S + 2 * D -Y/2);


    font.loadFromFile("img/font.ttf");
    leader.setFont(font);
    leader.setString("LEADERBOARD");
    leader.setCharacterSize(80);
    leader.setPosition({1250.f, 180.f});
    std::fstream file("wyniki.txt");
    for(int i = 0; i < 5; i++) {
        score_text[i].setPosition({1300.f, 180.f + (i+1) * 120.f});
        score_text[i].setFont(font);
        score_text[i].setCharacterSize(75);
        int x; file >> x;
        score_text[i].setString(std::to_string(x));
    }
}
