
#include "Fish.hpp"
#include <iostream>

void Fish::draw(sf::RenderWindow & window) {
    window.draw(sprite);
    // window.draw(circle);
}

void Fish::move(float diff) {
    if(direction == 0) {
        if(x < 1920+700) {
            x += (1000/log(mass/10) * diff);
        } else {
            dead = true;
        }
    } else {
        if (x > 0-700) {
            x -= (1000/log(mass/10) * diff);
        } else {
            dead = true;
        }
    }
    circle.setPosition(x, y);
    sprite.setPosition(x, y);
}

int Fish::getMass() {
    return mass;
}

bool Fish::isDead() {
    return dead;
}

void Fish::kill() {
    dead = true;
}

float Fish::getRadius() {
    return circle.getRadius();
}

sf::Vector2f Fish::getPosition() {
    return {x, y};
}

Fish::Fish(int player_mass, int skin) {
    mass = rand()%(int)(2*player_mass) + (player_mass/3);
    direction = rand()%2;
    
    float radius = sqrt(mass);
    circle.setRadius(radius);
    circle.setOrigin({radius, radius});
    circle.setPosition(x, y);
    sprite.setPosition(x, y);

    float s = circle.getRadius() / 209.f;
    sprite.setScale(s, s);

    texture[0].loadFromFile("img/player1.png");
    texture[1].loadFromFile("img/player2.png");
    sprite.setTexture(texture[skin]);
    sprite.setOrigin({482, 417});

    int sx = sprite.getTexture()->getSize().x, sy = sprite.getTexture()->getSize().y;
    if(!direction){
        x = 0-700 - radius;
        sprite.setTextureRect(sf::IntRect(0, 0, sx, sy));
    } else {
        x = 1920+700-radius;
        sprite.setTextureRect(sf::IntRect(sx, 0, -sx, sy));
    }
    y = rand()%1080 - radius;

}