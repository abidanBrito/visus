#include "App.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <string.h>

void errorCallback(int errorCode, const char* description)
{
    std::cerr << errorCode << ": " << description << '\n';
}

App::App()
{
    // Initialize GLFW and assign error callback
    glfwSetErrorCallback(errorCallback);
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
    m_renderWindow =
        glfwCreateWindow(m_renderWindowSizeX, m_renderWindowSizeY, "Visus3D", NULL, NULL);
    if (m_renderWindow == nullptr)
    {
        std::cout << "[ERROR] - Failed to create the window!\n";
        glfwTerminate();
    }

    // Load window icon
    GLFWimage windowIcons[1];
    windowIcons[0].pixels = stbi_load("C:/Users/abi/Pictures/logo.png", &windowIcons[0].width,
                                      &windowIcons[0].height, 0, 4);
    glfwSetWindowIcon(m_renderWindow, 1, windowIcons);
    stbi_image_free(windowIcons[0].pixels);

    makeRenderContextCurrent();

    glfwSetWindowUserPointer(m_renderWindow, static_cast<void*>(this));
    glfwSetFramebufferSizeCallback(m_renderWindow, &framebufferSizeCallbackRenderWindow);

    glbinding::initialize(glfwGetProcAddress);
}

void App::frameloop()
{
    while (!glfwWindowShouldClose(m_renderWindow))
    {
        update();
        render();
        glfwSwapBuffers(m_renderWindow);
    }
}

void App::update()
{
    glfwPollEvents();
}

void App::render()
{
    // Clear the back buffer
    clear(true, false, false);
}

void App::clear(bool colorBuffer, bool depthBuffer, bool stencilBuffer)
{
    ClearBufferMask bufferMask =
        (colorBuffer ? ClearBufferMask::GL_COLOR_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT)
        | (depthBuffer ? ClearBufferMask::GL_DEPTH_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT)
        | (stencilBuffer ? ClearBufferMask::GL_STENCIL_BUFFER_BIT : ClearBufferMask::GL_NONE_BIT);

    glClearColor(1.f, 1.f, 0.f, 1.f);
    glClear(bufferMask);
}

void App::exit()
{
    glfwDestroyWindow(m_renderWindow);
    glfwTerminate();
}

GLFWwindow* App::getRenderWindow()
{
    return m_renderWindow;
}

void App::setRenderWindowSize(const int width, const int height)
{
    m_renderWindowSizeX = width;
    m_renderWindowSizeY = height;
}

void App::setWindowTitle(const std::string& name)
{
    glfwSetWindowTitle(m_renderWindow, name.c_str());
}

void App::framebufferSizeCallbackRenderWindow(GLFWwindow* window, int width, int height)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    app->setRenderWindowSize(width, height);
}

void App::makeRenderContextCurrent()
{
    glfwMakeContextCurrent(m_renderWindow);
}
