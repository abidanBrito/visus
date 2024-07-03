#pragma once

#include "Window.hpp"

class App
{
public:
    App();
    void frameloop();
    void clearWindowBuffers(bool color_buffer, bool depth_buffer, bool stencil_buffer);

private:
    Window m_window;

    void render();
    void update();
    void exit();
};
