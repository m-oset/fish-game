#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"


void Game::start() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Fish Game");

    sf::Clock clock;
    while(window.isOpen()) {
        float diff = clock.getElapsedTime().asSeconds();
        clock.restart();
        float fps = 1.f / diff;
        sf::Event event;
        if(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        // std::cout << fps << "\n";
        window.display();
        window.setFramerateLimit(60);
    }
}
