#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "../Main/Fonts.hpp"
#include "../Engine/State.hpp"

class Board {
private:
    const int BOARD_SIZE = 8;

    bool is_player[2] = {true, true};

    sf::Vector2i selected_cell_idx = sf::Vector2i(-1, -1);

    Engine::State game_state;


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
            position.x <= event.x && event.x < position.x + size &&
            position.y <= event.y && event.y < position.y + size;
    }

    void onClick(int i, int j) {
        if ((i ^ j ^ 1) & 1) return;
        selected_cell_idx = {j, i};
    }

    void handle(const sf::Event& event) {
        switch (event.type) {
            case sf::Event::MouseButtonPressed: {
                if (inBound(event.mouseButton)) {
                    onClick(floor((event.mouseButton.y - position.y)/(size/8)), floor(event.mouseButton.x - position.x) / (size/8));
                }
                break;
            }
        }
    }

    void render(sf::RenderWindow& win) {

        // Drawing background
        sf::RectangleShape background(sf::Vector2f(size, size));
        background.setFillColor(sf::Color(233, 217, 200));
        background.setPosition(position);

        win.draw(background);

        // Drawing Board Cells
        sf::RectangleShape cell;
        cell.setSize(sf::Vector2f(size/8, size/8));
        cell.setFillColor(sf::Color(130, 114, 99));

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i^j)&1) {
                    cell.setPosition(position + sf::Vector2f(size/8*j, size/8*i));
                    win.draw(cell);
                }
            }
        }

        // Drawing selected cell
        if (selected_cell_idx.x != -1) {
            cell.setFillColor(sf::Color(200, 174, 149));
            cell.setPosition(position + sf::Vector2f(size/8*selected_cell_idx.x, size/8*selected_cell_idx.y));
            win.draw(cell);
        }

        // Drawing Checkers
        float radius = size/20;
        sf::CircleShape circle(radius);
        circle.setOutlineColor(sf::Color(50, 200, 50));
        for (int i = 0; i < 8; i++) {
            for (int j = (i&1)^1; j < 8; j += 2) {
                auto type = game_state.get(i, j);
                circle.setPosition(position + sf::Vector2f(size/8*j + (size/16 - radius), size/8*i + (size/16 - radius)));
                switch (type) {
                    case Engine::CellType::BLACK_PAWN: {
                        circle.setFillColor(sf::Color::Black);
                        circle.setOutlineThickness(0);
                        win.draw(circle);
                        break;
                    }
                    case Engine::CellType::WHITE_PAWN: {
                        circle.setFillColor(sf::Color::White);
                        circle.setOutlineThickness(0);
                        win.draw(circle);
                        break;
                    }
                    case Engine::CellType::BLACK_QUEEN: {
                        circle.setFillColor(sf::Color::Black);
                        circle.setOutlineThickness(4);
                        win.draw(circle);
                        break;
                    }
                    case Engine::CellType::WHITE_QUEEN: {
                        circle.setFillColor(sf::Color::White);
                        circle.setOutlineThickness(4);
                        win.draw(circle);
                        break;
                    }
                }
            }
        }
    }
};