#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "./Form.hpp"
#include "../Components/Button.hpp"
#include "../Components/TextBox.hpp"
#include "../Main/Bridge.hpp"
#include "../Main/Fonts.hpp"


class FinishForm : public IForm {
public:
    Button back  = Button("Back");
    TextBox p_text = TextBox();

    void onBack() {
        bridge->openForm(0, {});
    }

    void init(std::map<std::string, std::string> options) override {
        p_text.content = "Winner: " + options["winner"];
    }

    FinishForm(Bridge& bridge) {
        this->bridge = &bridge;

        p_text.bounds.left = 200;
        p_text.bounds.top = 200;
        p_text.bounds.width = 200;
        p_text.text_align = TextAlign::CENTER;

        back.position = sf::Vector2f(200,450);
        back.size = sf::Vector2f(200, 70);
        back.clb_onclick = std::bind(&FinishForm::onBack, this);
    }

    void handle(const sf::Event& event) override {
        back.handle(event);
    }

    void render(sf::RenderWindow& win) override {
        back.render(win);
        p_text.render(win);
    }
};