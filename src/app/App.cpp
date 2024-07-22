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
        // Clear the back buffer
        clearWindowBuffers(true, false, false);
        glDisable(GL_CULL_FACE);
        ui::startFrame();

        // TODO(abi): render scene here...
        _renderer->render();

        ui::endFrame();
    }

    void App::clearWindowBuffers(bool color, bool depth, bool stencil)
    {
        ClearBufferMask bufferMask =
            (color ? ClearBufferMask::GL_COLOR_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT)
            | (depth ? ClearBufferMask::GL_DEPTH_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT)
            | (stencil ? ClearBufferMask::GL_STENCIL_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT);

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(bufferMask);
    }
} // namespace visus
