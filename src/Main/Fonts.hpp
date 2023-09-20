#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

struct Fonts {
    sf::Font mainFont;

    Fonts() {
        mainFont.loadFromFile("assets/Roboto-Regular.ttf");
    }
} fonts;