#pragma once

#include "Window.hpp"
#include "InputManager.hpp"

namespace visus
{
    class App
    {
    public:
        App();
        void frameloop();
        inline void clearWindowBuffers(bool color, bool depth, bool stencil);

    private:
        Window m_window;
        input::InputManager m_input;
        // UIManager m_ui;

        void render();
        void update();
        void exit();
    };
} // namespace visus
