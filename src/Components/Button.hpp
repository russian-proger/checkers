#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "../Main/Fonts.hpp"

class Button {
private:
    sf::RectangleShape rectShape;

    bool pressed = false;

public:
    sf::Vector2f position, size;
    sf::Text text = sf::Text();
    unsigned int fontSize = 16;
    sf::Color background = sf::Color::White;
    sf::Color color = sf::Color::Black;

    sf::Color pressed_background = sf::Color(200, 200, 200);
    std::function<void()> clb_onclick = [](){};

    Button(std::string text = "", sf::Vector2f size = sf::Vector2f(70, 100), sf::Vector2f position = sf::Vector2f(0, 0)) {
        this->text.setString(text);
        this->position = position;
        this->size = size;
    }

    bool inBound(const sf::Event::MouseButtonEvent& event) {
        return 
            position.x <= event.x && event.x <= position.x + size.x &&
            position.y <= event.y && event.y <= position.y + size.y;
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
                    clb_onclick();
                }
                pressed = false;
                break;
            }
        }
    }

    void render(sf::RenderWindow& win) {
        if (pressed) {
            rectShape.setFillColor(pressed_background);
        }
        else {
            rectShape.setFillColor(background);
        }
        rectShape.setOutlineThickness(1);
        rectShape.setOutlineColor(sf::Color::Black);
        rectShape.setSize(size);
        rectShape.setPosition(position);

        auto bounds = text.getLocalBounds();
        text.setPosition(sf::Vector2f(this->position.x + (this->size.x - bounds.width) / 2, this->position.y + (this->size.y - bounds.height) / 2));
        text.setFont(fonts.mainFont);
        text.setFillColor(color);
        win.draw(rectShape);
        win.draw(text);
        text.setCharacterSize(fontSize);
    }
};