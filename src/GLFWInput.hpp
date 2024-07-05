#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#endif

namespace visus
{
    namespace input
    {
        void glfwBindEventCallbacks(GLFWwindow* hwnd);
        void glfwOnKeyPress(GLFWwindow* hwnd, [[maybe_unused]] const int32_t key,
                            [[maybe_unused]] const int32_t scanCode,
                            [[maybe_unused]] const int32_t action,
                            [[maybe_unused]] const int32_t mods);
        void glfwOnMouseButtonPress(GLFWwindow* hwnd, [[maybe_unused]] const int32_t button,
                                    [[maybe_unused]] const int32_t action,
                                    [[maybe_unused]] const int32_t mods);
        void glfwOnCursorMove(GLFWwindow* hwnd, [[maybe_unused]] double xPos,
                              [[maybe_unused]] double yPos);
        void glfwOnScroll(GLFWwindow* hwnd, [[maybe_unused]] double xOffset,
                          [[maybe_unused]] double yOffset);
    } // namespace input
} // namespace visus
