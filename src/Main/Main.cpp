#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "./Fonts.hpp"

struct Bridge {
    std::function<void(int)> openForm;
    std::function<void()> exit;
    Bridge() {
        openForm = [](int){};
        exit = [](){};
    }
};

class Button {
private:
    sf::RectangleShape rectShape;

    bool pressed = false;

public:
    sf::Vector2f position, size;
    sf::Text text = sf::Text();
    unsigned int fontSize = 16;
    sf::Color background = sf::Color::White;
    sf::Color color = sf::Color::Black;

    sf::Color pressed_background = sf::Color(200, 200, 200);
    std::function<void()> clb_onclick = [](){};

    Button(std::string text = "", sf::Vector2f size = sf::Vector2f(70, 100), sf::Vector2f position = sf::Vector2f(0, 0)) {
        this->text.setString(text);
        this->position = position;
        this->size = size;
    }

    bool inBound(const sf::Event::MouseButtonEvent& event) {
        return 
            position.x <= event.x && event.x <= position.x + size.x &&
            position.y <= event.y && event.y <= position.y + size.y;
    }

    void handle(const sf::Event& event) {
        switch (event.type) {
            case sf::Event::MouseButtonPressed: {
                if (inBound(event.mouseButton)) {
                    pressed = true;
                }
                break;
            }
            case sf::Event::MouseButtonReleased: {
                if (pressed && inBound(event.mouseButton)) {
                    clb_onclick();
                }
                pressed = false;
                break;
            }
        }
    }

    void render(sf::RenderWindow& win) {
        if (pressed) {
            rectShape.setFillColor(pressed_background);
        }
        else {
            rectShape.setFillColor(background);
        }
        rectShape.setOutlineThickness(2);
        rectShape.setOutlineColor(sf::Color::Black);
        rectShape.setSize(size);
        rectShape.setPosition(position);

        auto bounds = text.getLocalBounds();
        text.setPosition(sf::Vector2f(this->position.x + (this->size.x - bounds.width) / 2, this->position.y + (this->size.y - bounds.height) / 2));
        text.setFont(fonts.mainFont);
        text.setFillColor(color);
        win.draw(rectShape);
        win.draw(text);
        text.setCharacterSize(fontSize);
    }
};

class IForm {
protected:
    Bridge* bridge;
public:
    IForm(){}
    virtual void handle(const sf::Event&) {};
    virtual void render(sf::RenderWindow&) {};
};

class HomeForm : public IForm {
public:
    Button quit = Button("Quit");

    void onQuit() {
        bridge->exit();
    }

    HomeForm(Bridge& bridge) {
        this->bridge = &bridge;
        quit.position = sf::Vector2f(200,400);
        quit.size = sf::Vector2f(200, 70);
        quit.clb_onclick = std::bind(&HomeForm::onQuit, this);
    }

    void handle(const sf::Event& event) override {
        quit.handle(event);
    }

    void render(sf::RenderWindow& win) override {
        // sf::RectangleShape rect(sf::Vector2f(100, 150));
        // rect.setOutlineColor(sf::Color::Green);
        // rect.setOutlineThickness(10);
        // rect.setPosition(sf::Vector2f(50, 50));
        quit.render(win);
    }
};

int main() {
    sf::VideoMode vmode = sf::VideoMode(600, 800);
    sf::RenderWindow win = sf::RenderWindow(vmode, "Checkers", sf::Style::Titlebar | sf::Style::Close);


    Bridge bridge;

    std::vector<IForm*> forms = {
        (IForm*)(new HomeForm(bridge))
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

        win.clear();
        forms[activeFormID]->render(win);
        win.display();

        sf::sleep(sf::milliseconds(16));
    }
 
    return 0;
}