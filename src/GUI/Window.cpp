#include "Window.hpp"

gui::Window::Window() {}

gui::Window::Window(std::shared_ptr<gui::Form> form_ptr) {
    this->setActiveForm(form_ptr);
    this->open();
}

gui::Window::~Window() {
    
}

void gui::Window::open() {
    auto thread = std::make_shared<sf::Thread>(&gui::Window::loop, this);
    this->loop_thread = thread;
    thread->launch();
}

void gui::Window::loop() {
    auto vmode = sf::VideoMode(320, 480);
    auto win = std::make_shared<sf::RenderWindow>(vmode, "Checkers");

    this->loop_mutex.lock();
    this->render_window = win;
    this->loop_mutex.unlock();

    while (win->isOpen()) {
        this->loop_mutex.lock();
        sf::Event event;

        // if (this->active_form.operator->)
        // std::mutex

        while (win->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    win->close();
                    break;
            }
        }

        this->loop_mutex.unlock();
        sf::sleep(sf::milliseconds(16));
    }

    win->close();
}

void gui::Window::close() {
    this->loop_mutex.lock();
    this->render_window->close();
    this->loop_mutex.unlock();

    this->loop_thread->wait();
}

void gui::Window::setActiveForm(std::shared_ptr<gui::Form> form_ptr) {
    
    this->active_form_ptr = form_ptr;
    
}