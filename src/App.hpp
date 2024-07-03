#pragma once

#include "Window.hpp"
#include "InputManager.hpp"

class App
{
public:
    App();
    void frameloop();
    void clearWindowBuffers(bool color, bool depth, bool stencil);

private:
    Window m_window;
    // InputManager m_input;

    void render();
    void update();
    void exit();
};
