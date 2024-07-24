#include "App.hpp"
#include "../ui/UI.hpp"

using namespace gl;

namespace visus
{
    App::App()
        : _window{Window()},
          _input{input::InputManager(_window.getHandle())}
    {
        _window.setIcon("res/img/logo.png");
        _window.setVSync(true);

        auto hwnd = _window.getHandle();
        glfwSetWindowUserPointer(hwnd, &_window);

        _scene = std::make_unique<graphics::Scene>(this);
        _renderer = std::make_unique<graphics::VolumeRenderer>(this);

        ui::initialize(hwnd);
        ui::font("res/fonts/roboto_medium.ttf");
    }

    void App::frameloop()
    {
        auto hwnd = _window.getHandle();
        while (!glfwWindowShouldClose(hwnd))
        {
            update();
            render();
            glfwSwapBuffers(hwnd);
        }

        _window.destroy();
        glfwTerminate();
    }

    void App::update()
    {
        glfwPollEvents();
        // NOTE(abi): for interactive scenes, we can update it here
    }

    void App::render()
    {
        // Depth testing
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);

        // Clear the back buffers
        glDisable(GL_CULL_FACE);
        clearWindowBuffers(true, true, false);

        ui::startFrame();

        _renderer->render();

        ui::endFrame();
    }

    void App::clearWindowBuffers(bool color, bool depth, bool stencil)
    {
        ClearBufferMask bufferMask =
            (color ? ClearBufferMask::GL_COLOR_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT)
            | (depth ? ClearBufferMask::GL_DEPTH_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT)
            | (stencil ? ClearBufferMask::GL_STENCIL_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT);

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClearDepth(1.0f);
        glClear(bufferMask);
    }
} // namespace visus
