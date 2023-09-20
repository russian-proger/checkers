#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "./Form.hpp"
#include "../Components/Button.hpp"
#include "../Main/Bridge.hpp"
#include "../Main/Fonts.hpp"


class HomeForm : public IForm {
public:
    Button play = Button("Play");
    Button quit  = Button("Quit");

    void onQuit() {
        bridge->exit();
    }

    void onPlay() {
        bridge->openForm(1);
    }

    HomeForm(Bridge& bridge) {
        this->bridge = &bridge;

        quit.position = sf::Vector2f(200,400);
        quit.size = sf::Vector2f(200, 70);
        quit.clb_onclick = std::bind(&HomeForm::onQuit, this);

        play.position = sf::Vector2f(200,300);
        play.size = sf::Vector2f(200, 70);
        play.clb_onclick = std::bind(&HomeForm::onPlay, this);
    }

    void handle(const sf::Event& event) override {
        quit.handle(event);
        play.handle(event);
    }

    void render(sf::RenderWindow& win) override {
        quit.render(win);
        play.render(win);
    }
};