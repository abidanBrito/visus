#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#endif

// #include <utility>

// struct CursorData
// {
//     int32_t mode;
//     float x, y;
// };

class InputManager
{
public:
    void bindEventCallbacks(GLFWwindow* hwnd) const;
    // inline static void setCursorMode(GLFWwindow* hwnd, const int32_t mode);
    // inline int32_t getCursorMode();
    // inline std::pair<float, float> getCursorPosition();

private:
    // static CursorData m_cursor;
    // static void updateCursorPosition(const float xPos, const float yPos);

    // Keyboard/mouse interactions
    static void onKeyPress(GLFWwindow* hwnd, const int32_t key, const int32_t scanCode,
                           const int32_t action, const int32_t mods);
    static void onMouseButtonPress(GLFWwindow* hwnd, const int32_t button, const int32_t action,
                                   const int32_t mods);
    static void onCursorMove(GLFWwindow* hwnd, const double xPos, const double yPos);
    static void onScroll(GLFWwindow* hwnd, const double xOffset, const double yOffset);
};
