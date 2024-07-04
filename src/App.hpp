#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "UIManager.hpp"

class App
{
public:
    App();
    void frameloop();
    inline void clearWindowBuffers(bool color, bool depth, bool stencil);

private:
    Window m_window;
    InputManager m_input;
    UIManager m_ui;

    void render();
    void update();
    void exit();
};
