#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "../Main/Fonts.hpp"

enum TextAlign {
    LEFT,
    RIGHT,
    CENTER,
};

class TextBox {
public:
    sf::Text text = sf::Text();
    sf::Color color, background;
    std::string content;
    TextAlign text_align;

    sf::FloatRect bounds;

    TextBox(std::string s = "") {
        text.setFont(fonts.mainFont);
        text_align = TextAlign::LEFT;
        content = s;
        color = sf::Color::White;
        background = sf::Color::Black;
    }

    void setPosition(sf::Vector2f pos) {
        bounds.left = pos.x;
        bounds.top = pos.y;
    }

    void setSize(sf::Vector2f size) {
        bounds.width = size.x;
        bounds.height = size.y;
    }

    void render(sf::RenderWindow& win) {
        text.setString(content);
        
        sf::Vector2f position(bounds.left, bounds.top);

        switch (text_align) {
            case TextAlign::CENTER: {
                position.x += (bounds.width - text.getLocalBounds().width) / 2;
                break;
            }
            case TextAlign::RIGHT: {
                position.x += (bounds.left - text.getLocalBounds().width);
                break;
            }
        }

        text.setPosition(position);

        text.setFillColor(color);

        sf::RectangleShape rect;
        rect.setPosition(sf::Vector2f(bounds.left, bounds.top));
        rect.setSize(sf::Vector2f(bounds.width, bounds.height));
        rect.setFillColor(background);

        win.draw(rect);
        win.draw(text);
    }
    
};