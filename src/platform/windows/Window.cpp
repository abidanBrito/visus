#include "Window.hpp"

namespace visus
{
    WindowInterface* WindowInterface::create(const WindowProperties& properties)
    {
        return new Window(properties);
    }

    Window::Window(const WindowProperties& properties)
    {
        init(properties);
    }

    Window::~Window()
    {
        shutdown();
    }

    void Window::init(const WindowProperties& properties)
    {
        details.width = properties.width;
        details.height = properties.height;
        details.title = properties.title;
        details.iconPath = properties.iconPath;
    }

    void Window::shutdown()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::setVSync(bool state)
    {
        glfwSwapInterval((state ? 1 : 0));
        details.vSync = state;
    }

    bool Window::isVSyncOn() const
    {
        return details.vSync;
    }

} // namespace visus
