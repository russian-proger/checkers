#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "./Form.hpp"
#include "../Components/Board.hpp"
#include "../Components/Button.hpp"
#include "../Main/Bridge.hpp"
#include "../Main/Fonts.hpp"



class PlayForm : public IForm {
public:
    Button back = Button("< Back");
    Board board = Board(400, sf::Vector2f(100, 150));

    void onBack() {
        bridge->openForm(0);
    }

    PlayForm(Bridge& bridge) {
        this->bridge = &bridge;

        back.position = sf::Vector2f(10,10);
        back.size = sf::Vector2f(150, 40);
        back.clb_onclick = std::bind(&PlayForm::onBack, this);
    }

    void handle(const sf::Event& event) override {
        back.handle(event);
        board.handle(event);
    }

    void render(sf::RenderWindow& win) override {
        back.render(win);
        board.render(win);
    }
};