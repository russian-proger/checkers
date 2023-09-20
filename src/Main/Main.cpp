#include "../GUI/Window.hpp"

#include "../Forms/MainForm.hpp"

#include <iostream>

int main() {
    gui::Window window(std::make_shared<gui::Form>(MainForm()));
    sf::sleep(sf::seconds(2));
    window.close();
    return 0;
}