#include "Window.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

using namespace gl;

Window::Window(uint32_t width, uint32_t height, const std::string& title, bool vSync)
    : m_handle{nullptr},
      m_properties{width, height, title, vSync}
{
    initialize();
    setVSync(vSync);
}

Window::Window(WindowData properties)
    : m_handle{nullptr},
      m_properties{properties}
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
    }

    // Setup GLFW with OpenGL
    glfwDefaultWindowHints();

    // NOTE(abi): by default GLFW may create a context with any OpenGL version. If a minimum
    // required version is specified, yet it is not supported, both context and window creation
    // will fail.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // Compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    // MSAA (no jaggies) & double buffering
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 16);

    // Create window
    m_handle = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title.c_str(),
                                NULL, NULL);
    if (m_handle == nullptr)
    {
        std::cout << "[ERROR] - Failed to create the window!\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_handle);

    glfwSetWindowUserPointer(m_handle, static_cast<void*>(this));
    glfwSetFramebufferSizeCallback(m_handle, &Window::framebufferSizeCallback);

    glbinding::initialize(glfwGetProcAddress);
}

void Window::destroy()
{
    glfwDestroyWindow(m_handle);
}

void Window::setTitle(const std::string& name)
{
    m_properties.title = name;
    glfwSetWindowTitle(m_handle, name.c_str());
}

void Window::setIcon(const std::string& path)
{
    // Load window icon
    GLFWimage windowIcons[1];
    windowIcons[0].pixels =
        stbi_load(path.c_str(), &windowIcons[0].width, &windowIcons[0].height, 0, 4);
    glfwSetWindowIcon(m_handle, 1, windowIcons);
    stbi_image_free(windowIcons[0].pixels);
}

void Window::setCursorMode(int32_t mode)
{
    glfwSetInputMode(m_handle, GLFW_CURSOR, mode);
}

void Window::setVSync(bool state)
{
    glfwSwapInterval((state ? 1 : 0));
    m_properties.vSync = state;
}

GLFWwindow* Window::getHandle() const
{
    return m_handle;
}

uint32_t Window::getWidth() const
{
    return m_properties.width;
}

uint32_t Window::getHeight() const
{
    return m_properties.height;
}

std::string Window::getTitle() const
{
    return m_properties.title;
}

bool Window::isVSyncOn() const
{
    return m_properties.vSync;
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

    // Retain viewport size
    window->m_properties.width = width;
    window->m_properties.height = height;

    // NOTE(abi): not sure if this is needed...
    // glViewport(0, 0, width, height);

    // Redraw window to account for viewport size changes
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window->m_handle);
}
