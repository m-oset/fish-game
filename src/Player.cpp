#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include <cmath>

void Player::update(int width, int height) {
    float s = circle.getRadius() / 209.f;
    sprite.setScale(s * width / 1920.f, s * height / 1080.f);
}

void Player::setStartingPosition(int width, int height) {
    dead = false;
    dir = 1;
	x = width/2.0;
    y = height/2.0;
	int x = sprite.getTexture()->getSize().x, y = sprite.getTexture()->getSize().y;
    sprite.setTextureRect(sf::IntRect(x, 0, -x, y));
}

int Player::getMass() {
    return mass;
}

void Player::draw(sf::RenderWindow & window) {
    window.draw(sprite);
    // window.draw(circle);
}

void Player::move(float diff, int width, int height) {
    // std::cout << event.key.code << "\n";
    bool ndir = dir;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        x -= 400*diff * width/1920.f;
        ndir = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        x += 400*diff * width/1920.f;
        ndir = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        y -= 300*diff * height/1080.f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        y += 300*diff * height/1080.f;
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
    
    if(x < -100*(width/1920.f) or x > width + (100*width/1920.f)) {
        dead = true;
    }
    if(y < -100*(height/1080.f) or y > height + (100*height/1080.f)) {
        dead = true;
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

void Player::grow(int fish_mass, int width, int height) {
    mass += (int)(2*sqrt(fish_mass));
    float radius = sqrt(mass);
    circle.setRadius(radius);
    circle.setScale({width/1920.f, height/1080.f});
    circle.setOrigin({radius, radius});
    circle.setPosition(x, y);
    sprite.setPosition(x, y);
    update(width, height);
}

void Player::setMass(int new_mass, int width, int height) {
    mass = new_mass;
    float radius = sqrt(mass);
    circle.setRadius(radius);
    circle.setScale({width/1920.f, height/1080.f});
    circle.setOrigin({radius, radius});
    circle.setPosition(x, y);
    sprite.setPosition(x, y);
    update(width, height);
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
