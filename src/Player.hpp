#pragma once

class Player {
    float x, y;
    public:
    void setStartingPosition();
    void draw(sf::RenderWindow & window);
    void move(float diff);
};