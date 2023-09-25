#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "./Form.hpp"
#include "../Components/Board.hpp"
#include "../Components/Button.hpp"
#include "../Components/TextBox.hpp"
#include "../Main/Bridge.hpp"
#include "../Main/Fonts.hpp"

#include "../Engine/Types.hpp"

std::string lead0(long long n, long long c = 2) {
    std::string ret = std::to_string(n);
    while (ret.size() < c) ret = "0" + ret;
    return ret;
}

std::string formatTime(long long t) {
    return lead0(t/60%60) + ":" + lead0(t%60);
}

class PlayForm : public IForm {
public:
    Button back = Button("< Back");
    Board board = Board(400, sf::Vector2f(100, 150));

    TextBox p1_timebox, p2_timebox;

    Engine::PlayerColor currentPlayer = Engine::PlayerColor::WHITE;
    bool started = 0;
    long long p1_time, p2_time;
    sf::Clock clock;

    void onBack() {
        bridge->openForm(0, {});
    }

    void onFinish(Engine::PlayerColor pc) {
        if (pc == Engine::PlayerColor::WHITE) {
            bridge->openForm(2, {{"winner", "Player 1"}});
        } else {
            bridge->openForm(2, {{"winner", "Player 2"}});
        }
    }

    void onStep(Engine::PlayerColor pc) {
        started = 1;
        currentPlayer = (Engine::PlayerColor)!pc;
    }

    void init(std::map<std::string,std::string> options) override {
        board.reset();
        board.clb_onfinish = std::bind(&PlayForm::onFinish, this, std::placeholders::_1);
        board.clb_onstep = std::bind(&PlayForm::onStep, this, std::placeholders::_1);
        p1_time = 5 * 60 * 1000000;
        p2_time = 5 * 60 * 1000000;
        currentPlayer = Engine::PlayerColor::WHITE;
        clock.restart();
    }

    PlayForm(Bridge& bridge) {
        this->bridge = &bridge;

        back.position = sf::Vector2f(10,10);
        back.size = sf::Vector2f(150, 40);
        back.clb_onclick = std::bind(&PlayForm::onBack, this);

        board.clb_onclick = [](int a, int b){std::cout << a << ' ' << b << std::endl;};
    }

    void handle(const sf::Event& event) override {
        back.handle(event);
        board.handle(event);
    }

    void render(sf::RenderWindow& win) override {
        sf::Text p1_name, p2_name;


        p1_name.setString("Player 1");
        p2_name.setString("Player 2");

        p1_name.setFont(fonts.mainFont);
        p2_name.setFont(fonts.mainFont);

        p1_name.setPosition(100, 560);
        p2_name.setPosition(100, 100);

        p1_timebox.content = formatTime(p1_time / 1000000);
        p2_timebox.content = formatTime(p2_time / 1000000);
        p1_timebox.setPosition(sf::Vector2f(400, 560));
        p2_timebox.setPosition(sf::Vector2f(400, 100));
        p1_timebox.setSize(sf::Vector2f(100, 40));
        p2_timebox.setSize(sf::Vector2f(100, 40));
        p1_timebox.text_align = TextAlign::CENTER;
        p2_timebox.text_align = TextAlign::CENTER;
        p1_timebox.background = sf::Color(50, 50, 50);
        p2_timebox.background = sf::Color(50, 50, 50);
        if (currentPlayer == Engine::PlayerColor::WHITE) {
            p1_timebox.background = sf::Color(120, 120, 120);
            p1_time -= clock.getElapsedTime().asMicroseconds();
        }
        else {
            p2_timebox.background = sf::Color(120, 120, 120);
            p2_time -= clock.getElapsedTime().asMicroseconds();
        }

        if (p1_time < 0) onFinish(Engine::PlayerColor::BLACK);
        if (p2_time < 0) onFinish(Engine::PlayerColor::WHITE);

        clock.restart();

        win.draw(p1_name);
        win.draw(p2_name);
        p1_timebox.render(win);
        p2_timebox.render(win);
        back.render(win);
        board.render(win);
    }
};