#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

struct Bridge {
    std::function<void(int)> openForm;
    Bridge() {
        openForm = [](int){};
    }
};

class IForm {
public:
    IForm(){}
    virtual void handle(const sf::Event&, Bridge&) {};
    virtual void render(sf::RenderWindow&, Bridge&) {};
};

class HomeForm : public IForm {
public:
    void handle(const sf::Event& event, Bridge& bridge) override {

    }
    void render(sf::RenderWindow& win, Bridge& bridge) override {

    }
};

int main() {
    sf::VideoMode vmode = sf::VideoMode(320, 480);
    sf::RenderWindow win = sf::RenderWindow(vmode, "Checkers", sf::Style::Titlebar | sf::Style::Close);

    std::vector<IForm*> forms = {
        (IForm*)(new HomeForm())
    };
    int activeFormID = 0;

    Bridge bridge;
    bridge.openForm = [&activeFormID](int id) { activeFormID = id; };

    sf::Event event;
    while (win.isOpen()) {
        while (win.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    win.close();
                    break;
                }
            }
            forms[activeFormID]->handle(event, bridge);
        }

        win.clear();
        forms[activeFormID]->render(win, bridge);
        win.display();

        sf::sleep(sf::milliseconds(16));
    }
 
    return 0;
}