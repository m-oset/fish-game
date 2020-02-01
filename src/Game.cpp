#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Player.hpp"


void Game::start() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Fish Game");

    sf::Clock clock;
    window.setFramerateLimit(60);
    Player player;
    player.setStartingPosition();
    while(window.isOpen()) {
        
        float diff = clock.getElapsedTime().asSeconds();
        clock.restart();
        // float fps = 1.f / diff;
        sf::Event event;
        if(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            player.move(diff);
        }
        window.clear();
        player.draw(window);
        // std::cout << fps << "\n";
        window.display();
        
    }
}
