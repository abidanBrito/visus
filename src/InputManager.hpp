#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#endif

// struct CursorData
// {
//     int32_t mode;
//     double x, y;
// };

class App;

class InputManager
{
public:
    InputManager(GLFWwindow* hwnd = nullptr);
    // CursorData* getCursorPosition();

private:
    // CursorData m_cursor;

    static void keyCallback(GLFWwindow* hwnd, int key, int scanCode, int action, int mods);
    static void cursorPosCallback(GLFWwindow* hwnd, double xPos, double yPos);
    static void mouseButtonCallback(GLFWwindow* hwnd, int button, int action, int mods);
    static void scrollCallback(GLFWwindow* hwnd, double xOffset, double yOffset);
};
