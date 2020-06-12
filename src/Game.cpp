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
            player.grow(fish->getMass(), width, height);
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

        int x = player.getMass() - default_mass;
        score_text.setString(std::to_string(x));
        score_text.setPosition(width/2.f - score_text.getGlobalBounds().width/2, height/2.f - 300*height/1080.f - score_text.getGlobalBounds().height/2);
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

        menu.update(width, height);
    }
}

void Game::startGame() {
    isPause = isGameOver = false;
    gameover_time = 0;
    player.setStartingPosition(width, height);
    player.setMass(default_mass, width, height);
}

void Game::start() {
    sf::Clock clock;
    window.setFramerateLimit(60);

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
                if(isPause and event.key.code == sf::Keyboard::Space) {
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
            player.setPosition(400 * width / 1920.f, 500 * height / 1080.f);
            player.setMass(10000, width, height);
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
    player.move(diff, width, height);
    for(auto& i : fish) {
        i->move(diff, width);
    }

    last_spawn += diff;
    if(last_spawn >= 1.5f) {
        last_spawn = 0.f;
        fish.push_back(new Fish(player.getMass(), player.getSkin(), width, height));
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
    window.create(sf::VideoMode(width, height), "Fish Game", sf::Style::Fullscreen);
    menu.update(width, height);
    background_texture.loadFromFile("img/background2.png");
    background.setTexture(background_texture);
    background.setPosition(0, 0);
    background.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    background.setScale({width / 1920.f, height / 1080.f});

    gameoverfish_texture.loadFromFile("img/dead.png");
    gameoverfish.setTexture(gameoverfish_texture);
    gameoverfish.setScale({width / 1920.f, height / 1080.f});
    gameoverfish.setPosition({
        width/2.f - gameoverfish.getGlobalBounds().width / 2.f,
        height/2.f - gameoverfish.getGlobalBounds().height / 2.f
    });

    font.loadFromFile("img/font.ttf");
    score_text.setFont(font);
    score_text.setCharacterSize(100);
    score_text.setScale({width / 1920.f, height / 1080.f});
}

Game::~Game() {
    for(auto& i : fish) {
        delete i;
    }
    fish.clear();
}
