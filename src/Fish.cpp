
#include "Fish.hpp"
#include <iostream>

void Fish::draw(sf::RenderWindow & window) {
    window.draw(sprite);
    // window.draw(circle);
}

void Fish::move(float diff, int width) {
    if(direction == 0) {
        if(x < width+700 * width/1920.f) {
            x += ((1000*width/1920.f)/log(mass/10) * diff);
        } else {
            dead = true;
        }
    } else {
        if (x > -700*width/1920.f) {
            x -= ((1000*width/1920.f)/log(mass/10) * diff);
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

Fish::Fish(int player_mass, int skin, int width, int height) {
    mass = rand()%(int)(2*player_mass) + (player_mass/3);
    direction = rand()%2;
    
    float radius = sqrt(mass);
    circle.setRadius(radius);
    circle.setScale({width/1920.f, height/1080.f});
    circle.setOrigin({radius, radius});

    float s = circle.getRadius() / 209.f;
    sprite.setScale(s * width/1920.f, s * height/1080.f);

    texture[0].loadFromFile("img/player1.png");
    texture[1].loadFromFile("img/player2.png");
    sprite.setTexture(texture[skin]);
    sprite.setOrigin({482, 417});

    int sx = sprite.getTexture()->getSize().x, sy = sprite.getTexture()->getSize().y;
    if(!direction){
        x = 0-(700*width/1920.f) - (radius*width/1920.f);
        sprite.setTextureRect(sf::IntRect(0, 0, sx, sy));
    } else {
        x = width+(700*width/1920.f)-(radius*width/1920.f);
        sprite.setTextureRect(sf::IntRect(sx, 0, -sx, sy));
    }
    y = rand()%height - (radius*height/1080.f);
    circle.setPosition(x, y);
    sprite.setPosition(x, y);
}
