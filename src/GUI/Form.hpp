#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

namespace gui {
    class Form {
    protected:
        std::shared_ptr<sf::RenderWindow> window;

    public:
        Form();
        ~Form();

        void init();
        void draw(std::shared_ptr<sf::RenderWindow>);
        void handle(const sf::Event&);
    };
}