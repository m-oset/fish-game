#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"


void Player::setStartingPosition(){
    x = 640.0 - 50.f;
    y = 360.0 - 50.f;
}
void Player::draw(sf::RenderWindow & window) {
    sf::CircleShape shape(10);
    shape.setRadius(50.f);
    shape.setPosition(x, y);
    window.draw(shape);
}

void Player::move(float diff) {
    // std::cout << event.key.code << "\n";
    if(sf:: Keyboard:: isKeyPressed (sf::Keyboard::Left)){
        x -= 200*diff;
    }
    if(sf:: Keyboard:: isKeyPressed (sf::Keyboard::Right)) {
        x += 200*diff;
    }
    if(sf:: Keyboard:: isKeyPressed (sf::Keyboard::Up)) {
        y -= 200*diff;
    }
    if(sf:: Keyboard:: isKeyPressed (sf::Keyboard::Down)) {
        y += 200*diff;
    }
}