#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include <cmath>


void Player::update() {
    float s = circle.getRadius() / 209.f;
    sprite.setScale(s, s);
}

void Player::setStartingPosition() {
    dead = false;
    mass = 500;
    dir = 0;

    circle.setFillColor(sf::Color::Red);
    float radius = sqrt(mass);
    x = 1920.0/2 - radius;
    y = 1080.0/2 - radius;
    circle.setRadius(radius);
    circle.setOrigin({radius, radius});
    circle.setPosition(x, y);
    update();
    sprite.setPosition(x, y);
}

int Player::getMass() {
    return mass;
}

void Player::draw(sf::RenderWindow & window) {
    window.draw(sprite);
    // window.draw(circle);
}

void Player::move(float diff) {
    // std::cout << event.key.code << "\n";
    bool ndir = dir;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        x -= 400*diff;
        ndir = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        x += 400*diff;
        ndir = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        y -= 300*diff;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        y += 300*diff;
    }

    if(ndir != dir) {
        int x = sprite.getTexture()->getSize().x, y = sprite.getTexture()->getSize().y;
        if(ndir == 0) {
            sprite.setTextureRect(sf::IntRect(0, 0, x, y));
        } else {
            sprite.setTextureRect(sf::IntRect(x, 0, -x, y));
        }
        dir = ndir;
    }

    circle.setPosition(x, y);
    sprite.setPosition(x, y);
}

float Player::getRadius() {
    return circle.getRadius();
}

void Player::setPosition(float nx, float ny) {
    x = nx, y = ny;
}

sf::Vector2f Player::getPosition() {
    return {x, y};
}

void Player::kill() {
    dead = true;
}

void Player::changeSkin() {
    cur_texture = 1 - cur_texture;
    sprite.setTexture(texture[cur_texture]);
}

int Player::getSkin() {
    return cur_texture;
}

void Player::grow(int fish_mass) {
    mass += (int)(5*sqrt(fish_mass));
    float radius = sqrt(mass);
    circle.setRadius(radius);
    circle.setOrigin({radius, radius});
    circle.setPosition(x, y);
    sprite.setPosition(x, y);
    update();
}

void Player::setMass(int new_mass) {
    mass = new_mass;
    float radius = sqrt(mass);
    circle.setRadius(radius);
    circle.setOrigin({radius, radius});
    circle.setPosition(x, y);
    sprite.setPosition(x, y);
    update();
}

bool Player::isDead() {
    return dead;
}

Player::Player() {
    texture[0].loadFromFile("img/player1.png");
    texture[1].loadFromFile("img/player2.png");
    sprite.setTexture(texture[cur_texture]);
    sprite.setOrigin({482, 417});
}