#pragma once

#include <memory>
#include <mutex>

#include <SFML/Graphics.hpp>

#include "Form.hpp"

namespace gui {

    class Window {
    private:
        std::shared_ptr<sf::Thread> loop_thread;
        void loop();

    // Loop using properties
        sf::Mutex loop_mutex;
        std::shared_ptr<gui::Form> active_form_ptr;
        std::shared_ptr<sf::RenderWindow> render_window;
    // Loop using properties

    public:
        Window();
        Window(std::shared_ptr<gui::Form>);
        ~Window();

        // Show window
        void open();

        // Close window
        void close();

        // Set New Form
        void setActiveForm(std::shared_ptr<gui::Form>);
    };
}