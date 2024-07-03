#include "App.hpp"

using namespace gl;

App::App()
    : m_window{Window()}
{
    m_window.setIcon("img/logo.png");
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
    // ...
}

void App::render()
{
    // Clear the back buffer
    clearWindowBuffers(true, false, false);
}

void App::clearWindowBuffers(bool colorBuffer, bool depthBuffer, bool stencilBuffer)
{
    ClearBufferMask bufferMask =
        (colorBuffer ? ClearBufferMask::GL_COLOR_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT)
        | (depthBuffer ? ClearBufferMask::GL_DEPTH_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT)
        | (stencilBuffer ? ClearBufferMask::GL_STENCIL_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT);

    glClearColor(1.f, 1.f, 0.f, 1.f);
    glClear(bufferMask);
}
