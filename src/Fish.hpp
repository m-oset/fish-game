#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Fish{
    float x, y;
    int mass;
    int direction; //0 - rybka płynie z lewej, 1 - rybka płynie z prawej
    bool dead = false;
    sf::CircleShape circle; 
    sf::Texture texture[2];
    sf::Sprite sprite;
public:
    // void setMass(float Player.mass);
    void draw(sf::RenderWindow & window);
    void move(float diff);
    int getMass();
    bool isDead();
    void kill();
    float getRadius();
    sf::Vector2f getPosition();
    Fish(int player_mass, int skin);
};