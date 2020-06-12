#pragma once

class Player {
    float x, y;
    int mass;
    sf::CircleShape circle;
    sf::Texture texture[2];
    int cur_texture = 1;
    sf::Sprite sprite;
    bool dead = false;
    bool dir = 0; // 0 - right 1 - left
    void update(int width, int height);
public:
    void setStartingPosition(int width, int height);
    int getMass();
    void draw(sf::RenderWindow & window);
    void move(float diff, int width, int height);
    float getRadius();
    void setPosition(float nx, float ny);
    sf::Vector2f getPosition();
    void kill();
    void changeSkin();
    int getSkin();
    void grow(int fish_mass, int width, int height);
    void setMass(int new_mass, int width, int height);
    bool isDead();
    Player();
};