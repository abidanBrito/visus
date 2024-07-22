#include "Window.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

using namespace gl;

namespace visus
{
    Window::Window(uint32_t width, uint32_t height, const std::string& title, bool vSync)
        : _handle{nullptr},
          _properties{width, height, title, vSync}
    {
        initialize();
        setVSync(vSync);
    }

    Window::Window(WindowData properties)
        : _handle{nullptr},
          _properties{properties}
    {
        initialize();
        setVSync(properties.vSync);
    }

    Window::~Window()
    {
        destroy();
    }

    void Window::initialize()
    {
        // Initialize GLFW and assign error callback
        glfwSetErrorCallback(Window::errorCallback);
        if (!glfwInit())
        {
            std::cerr << "Couldn't properly initialize GLFW.\n";
            exit(EXIT_FAILURE);
        }

        // Setup GLFW with OpenGL
        glfwDefaultWindowHints();

        // NOTE(abi): by default GLFW may create a context with any OpenGL version. If a minimum
        // required version is specified, yet it is not supported, both context and window creation
        // will fail.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        // Compatibility
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

        // MSAA (no jaggies) & double buffering
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_SAMPLES, 16);

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        // Create window
        _handle = glfwCreateWindow(_properties.width, _properties.height, _properties.title.c_str(),
                                   NULL, NULL);
        if (_handle == nullptr)
        {
            std::cout << "[ERROR] - Failed to create the window!\n";
            glfwTerminate();
        }

        glfwMakeContextCurrent(_handle);

        glfwSetWindowUserPointer(_handle, static_cast<void*>(this));
        glfwSetFramebufferSizeCallback(_handle, &Window::framebufferSizeCallback);

        glbinding::initialize(glfwGetProcAddress);

        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n'
                  << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n'
                  << "Vendor: " << glGetString(GL_VENDOR) << "\n\n";
    }

    void Window::destroy()
    {
        glfwDestroyWindow(_handle);
    }

    void Window::setTitle(const std::string& name)
    {
        _properties.title = name;
        glfwSetWindowTitle(_handle, name.c_str());
    }

    void Window::setIcon(const std::string& path)
    {
        // Load window icon
        GLFWimage windowIcons[1];
        windowIcons[0].pixels =
            stbi_load(path.c_str(), &windowIcons[0].width, &windowIcons[0].height, 0, 4);
        glfwSetWindowIcon(_handle, 1, windowIcons);
        stbi_image_free(windowIcons[0].pixels);
    }

    void Window::setCursorMode(int32_t mode)
    {
        glfwSetInputMode(_handle, GLFW_CURSOR, mode);
    }

    void Window::setVSync(bool state)
    {
        glfwSwapInterval((state ? 1 : 0));
        _properties.vSync = state;
    }

    GLFWwindow* Window::getHandle() const
    {
        return _handle;
    }

    uint32_t Window::getWidth() const
    {
        return _properties.width;
    }

    uint32_t Window::getHeight() const
    {
        return _properties.height;
    }

    std::string Window::getTitle() const
    {
        return _properties.title;
    }

    bool Window::isVSyncOn() const
    {
        return _properties.vSync;
    }

    void Window::errorCallback(int errorCode, const char* description)
    {
        std::cerr << errorCode << ": " << description << '\n';
    }

    void Window::framebufferSizeCallback(GLFWwindow* hwnd, int width, int height)
    {
        // NOTE(abi): we might not have multiple windows or race conditions, but
        // it seems like a good practice to check the handle anyway.
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
        if (window == NULL || window->getHandle() != hwnd)
        {
            return;
        }

        // Reset viewport
        glViewport(0, 0, width, height);

        // Redraw window to account for viewport size changes
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window->_handle);

        // Retain viewport size
        window->_properties.width = width;
        window->_properties.height = height;
    }
} // namespace visus
