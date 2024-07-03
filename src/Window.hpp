#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#endif

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

struct WindowData
{
    uint32_t width, height;
    std::string title;
    bool vSync;
};

class Window
{
public:
    Window(uint32_t width = 1280, uint32_t height = 720, const std::string& title = "MyApp",
           bool vSync = true);
    Window(WindowData properties);

    ~Window();
    void destroy();

    void setIcon(const std::string& path);
    void setTitle(const std::string& name);
    void setVSync(bool state);

    bool isVSyncOn() const;
    GLFWwindow* getHandle() const;
    uint32_t getWidth() const;
    uint32_t getHeight() const;
    std::string getTitle() const;

private:
    GLFWwindow* m_handle;
    WindowData m_properties;

    void initialize();
    static void errorCallback(int errorCode, const char* description);
    static void framebufferSizeCallback(GLFWwindow* hwnd, int width, int height);
};
