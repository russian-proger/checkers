#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "../Main/Fonts.hpp"

class Board {
private:
    sf::RectangleShape rectShape;

    bool pressed = false;
    const int BOARD_SIZE = 8;

public:
    sf::Vector2f position;
    float size;

    std::function<void(int,int)> clb_onclick = [](int, int){};

    Board(float size = 400, sf::Vector2f position = sf::Vector2f(0, 0)) {
        this->position = position;
        this->size = size;
    }

    bool inBound(const sf::Event::MouseButtonEvent& event) {
        return 
            position.x <= event.x && event.x <= position.x + size &&
            position.y <= event.y && event.y <= position.y + size;
    }


    void handle(const sf::Event& event) {
        switch (event.type) {
            case sf::Event::MouseButtonPressed: {
                if (inBound(event.mouseButton)) {
                    pressed = true;
                }
                break;
            }
            case sf::Event::MouseButtonReleased: {
                if (pressed && inBound(event.mouseButton)) {
                    clb_onclick(floor((event.mouseButton.y - position.y)/(size/8)), floor(event.mouseButton.x - position.x) / (size/8));
                }
                pressed = false;
                break;
            }
        }
    }

    void render(sf::RenderWindow& win) {
        sf::RectangleShape cell;
        cell.setSize(sf::Vector2f(size/8, size/8));
        cell.setFillColor(sf::Color(130, 114, 99));

        sf::RectangleShape background(sf::Vector2f(size, size));
        background.setFillColor(sf::Color(233, 217, 200));
        background.setPosition(position);

        win.draw(background);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i^j)&1) {
                    cell.setPosition(position + sf::Vector2f(size/8*j, size/8*i));
                    win.draw(cell);
                }
            }
        }
    }
};