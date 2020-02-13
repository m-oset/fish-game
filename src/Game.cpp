#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <vector>

void Game::eat(Fish* fish) {
    auto [x1, y1] = player.getPosition();
    auto [x2, y2] = fish->getPosition();
    float r1 = player.getRadius(), r2 = fish->getRadius();
    float distance = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    if(r1 + r2 >= distance) {
        if(r1 < r2) {
            player.kill();
        } else if (r1 > r2) {
            fish->kill();
            player.grow(fish->getMass());
        }
    }
}

void Game::gameOver() {
    if(player.isDead()) { 
        for(auto& i : fish) {
            delete i;
        }
        fish.clear();
        isGameOver = true;

        int x = player.getMass() - 500;
        score_text.setString(std::to_string(x));
        score_text.setPosition(1920/2 - score_text.getGlobalBounds().width/2, 1080/2 - 300 - score_text.getGlobalBounds().height/2);
        std::fstream file("wyniki.txt");
        std::vector <int> results;
        int res;
        while(file >> res) {
            results.push_back(res);
        }
        results.push_back(x);
        std::sort(results.rbegin(), results.rend());
        file.close();
        file.open("wyniki.txt");
        file.clear();
        for(int i = 0; i < 5; i++) {
            file << results[i] << "\n";
        }
        file.close();

        menu.update();
    }
}

void Game::startGame() {
    isPause = isGameOver = false;
    gameover_time = 0;
    player.setStartingPosition();
}

void Game::start() {
    sf::Clock clock;
    window.setFramerateLimit(60);
    player.setStartingPosition();
    while(window.isOpen()) {
        float diff = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(isGameOver and gameover_time >= 0.8f) {
                    isGameOver = false;
                    isPause = true;
                }
                if(event.key.code == sf::Keyboard::Space) {
                    startGame();
                }
            }
            if(event.type == sf::Event::MouseButtonPressed) {
                 if(isGameOver and gameover_time >= 0.8f) {
                    isGameOver = false;
                    isPause = true;
                }

                if(event.mouseButton.button == sf::Mouse::Left) {
                    float x = event.mouseButton.x;
                    float y = event.mouseButton.y;
                    if(isPause) {
                        if(menu.isPlayPressed(x, y)) {
                            startGame();
                        }
                        if(menu.isExitPressed(x, y)) {
                            window.close();
                        }
                        if(menu.isSkinChangePressed(x, y)) {
                            player.changeSkin();
                        }
                    }
                }
            }
        }

        if(isGameOver) {
            gameover_time += diff;
            window.clear(); 
            window.draw(background);
            window.draw(gameoverfish);
            window.draw(score_text);
        } else if(isPause) {
            player.setPosition(400, 500);
            player.setMass(10000);
            window.clear(); 
            window.draw(background);
            menu.draw(window);
            player.draw(window);
        } else {
            update(diff);
            gameOver();
            window.clear();
            draw();
        }

        window.display();
    }
}

void Game::update(float diff){
    player.move(diff);
    for(auto& i : fish) {
        i->move(diff);
    }

    last_spawn += diff;
    if(last_spawn >= 1.5f) {
        last_spawn = 0.f;
        fish.push_back(new Fish(player.getMass(), player.getSkin()));
    }
    for(auto& i : fish) {
        eat(i);
        if(player.isDead()) {
            return;
        }
    }

    for(int i = (int)fish.size() - 1; i >= 0; i--) {
        if(fish[i]->isDead()) {
            delete fish[i];
            fish.erase(fish.begin() + i);
        }
    }
}

void Game::draw(){
    window.draw(background);
    player.draw(window);
    for(auto& i : fish) {
        i->draw(window);
    }
}

Game::Game() {
    srand(time(0));
    window.create(sf::VideoMode(1920, 1080), "Fish Game", sf::Style::Close | sf::Style::Titlebar);
    background_texture.loadFromFile("img/background2.png");
    background.setTexture(background_texture);
    background.setPosition(0, 0);
    background.setTextureRect(sf::IntRect(0, 0, 1920, 1080));

    gameoverfish_texture.loadFromFile("img/dead.png");
    gameoverfish.setTexture(gameoverfish_texture);
    gameoverfish.setPosition({1920.f/2 - gameoverfish_texture.getSize().x / 2.f, 1080.f/2 - gameoverfish_texture.getSize().y / 2.f});

    font.loadFromFile("img/font.ttf");
    score_text.setFont(font);
    score_text.setCharacterSize(100);
    score_text.setString("1234567890");
}

Game::~Game() {
    for(auto& i : fish) {
        delete i;
    }
    fish.clear();
}