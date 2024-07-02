#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#endif

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

using namespace gl;

class App
{
public:
    App();
    void frameloop();
    GLFWwindow* getRenderWindow();
    void setWindowTitle(const std::string& name);
    void makeRenderContextCurrent();
    void clear(bool color_buffer, bool depth_buffer, bool stencil_buffer);

private:
    GLFWwindow* m_renderWindow;
    uint32_t m_renderWindowSizeX{1280};
    uint32_t m_renderWindowSizeY{720};

    // std::unique_ptr<InteractorGUI> m_interactorGUI;

    void setRenderWindowSize(int width, int height);
    static void framebufferSizeCallbackRenderWindow(GLFWwindow* window, int width, int height);

    void render();
    void update();
    void exit();
};
