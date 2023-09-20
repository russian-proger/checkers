#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "../Main/Bridge.hpp"
#include "../Main/Fonts.hpp"

class IForm {
protected:
    Bridge* bridge;
public:
    IForm(){}
    virtual void handle(const sf::Event&) {};
    virtual void render(sf::RenderWindow&) {};
};