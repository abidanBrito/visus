#include "App.hpp"

using namespace gl;

App::App()
    : m_window{Window()},
      m_input{InputManager()},
      m_ui{UIManager()}
{
    m_window.setIcon("res/img/logo.png");
    m_window.setVSync(true);

    auto hwnd = m_window.getHandle();
    m_input.bindEventCallbacks(hwnd);

    m_ui.initialize(hwnd);
    m_ui.font("res/fonts/roboto_medium.ttf");
}

void App::exit()
{
    m_window.destroy();
    glfwTerminate();
}

void App::frameloop()
{
    auto hwnd = m_window.getHandle();
    while (!glfwWindowShouldClose(hwnd))
    {
        update();
        render();
        glfwSwapBuffers(hwnd);
    }
}

void App::update()
{
    glfwPollEvents();

    // TODO(abi): update scene logic here...
}

void App::render()
{
    // Clear the back buffer
    clearWindowBuffers(true, false, false);

    m_ui.startFrame();

    // TODO(abi): render scene here...

    m_ui.endFrame();
}

void App::clearWindowBuffers(bool color, bool depth, bool stencil)
{
    ClearBufferMask bufferMask =
        (color ? ClearBufferMask::GL_COLOR_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT)
        | (depth ? ClearBufferMask::GL_DEPTH_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT)
        | (stencil ? ClearBufferMask::GL_STENCIL_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT);

    glClearColor(0.7f, 0.7f, 0.7f, 0.2f);
    glClear(bufferMask);
}
