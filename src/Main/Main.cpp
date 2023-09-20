#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "./Bridge.hpp"
#include "../Forms/HomeForm.hpp"
#include "../Forms/PlayForm.hpp"

int main() {
    sf::VideoMode vmode = sf::VideoMode(600, 800);
    sf::ContextSettings settings = sf::ContextSettings();
    settings.antialiasingLevel = 8;
    sf::RenderWindow win = sf::RenderWindow(vmode, "Checkers", sf::Style::Titlebar | sf::Style::Close, settings);


    Bridge bridge;

    std::vector<IForm*> forms = {
        (IForm*)(new HomeForm(bridge)),
        (IForm*)(new PlayForm(bridge))
    };

    int activeFormID = 0;
    
    bridge.openForm = [&activeFormID](int id) { activeFormID = id; };
    bridge.exit = [&](){ win.close(); };

    sf::Event event;
    while (win.isOpen()) {
        while (win.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    win.close();
                    break;
                }
            }
            forms[activeFormID]->handle(event);
        }

        win.clear(sf::Color(20, 20, 20));
        forms[activeFormID]->render(win);
        win.display();

        sf::sleep(sf::milliseconds(16));
    }
 
    return 0;
}