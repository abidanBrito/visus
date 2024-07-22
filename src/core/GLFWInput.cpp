#include "GLFWInput.hpp"
#include "InputHandler.hpp"
#include "Window.hpp"
#include <iostream>

namespace glfw
{
    bool ownWindowHandle(GLFWwindow* hwnd)
    {
        auto window = static_cast<visus::Window*>(glfwGetWindowUserPointer(hwnd));
        return (window == nullptr || window->getHandle() != hwnd) ? false : true;
    }

    void glfwOnKeyPress(GLFWwindow* hwnd, const int32_t key, const int32_t scanCode,
                        const int32_t action, const int32_t mods)
    {
        if (!ownWindowHandle(hwnd))
        {
            return;
        }

        if (visus::input::glfwInput.onKeyPress)
        {
            visus::input::glfwInput.onKeyPress(key, scanCode, action, mods);
        }
    }

    void glfwOnMouseButtonPress(GLFWwindow* hwnd, const int32_t button, const int32_t action,
                                const int32_t mods)
    {
        if (!ownWindowHandle(hwnd))
        {
            return;
        }

        if (visus::input::glfwInput.onMouseButtonPress)
        {
            visus::input::glfwInput.onMouseButtonPress(button, action, mods);
        }
    }

    void glfwOnCursorMove(GLFWwindow* hwnd, double xPos, double yPos)
    {
        if (!ownWindowHandle(hwnd))
        {
            return;
        }

        if (visus::input::glfwInput.onCursorMove)
        {
            visus::input::glfwInput.onCursorMove(xPos, yPos);
        }
    }

    void glfwOnScroll(GLFWwindow* hwnd, double xOffset, double yOffset)
    {
        if (!ownWindowHandle(hwnd))
        {
            return;
        }

        if (visus::input::glfwInput.onScroll)
        {
            visus::input::glfwInput.onScroll(xOffset, yOffset);
        }
    }
} // namespace glfw

namespace visus
{
    namespace input
    {
        void glfwBindEventCallbacks(GLFWwindow* hwnd)
        {
            // Keyboard interactions
            glfwSetKeyCallback(hwnd, &glfw::glfwOnKeyPress);
            glfwSetInputMode(hwnd, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

            // Mouse interactions
            glfwSetMouseButtonCallback(hwnd, &glfw::glfwOnMouseButtonPress);
            glfwSetCursorPosCallback(hwnd, &glfw::glfwOnCursorMove);
            glfwSetScrollCallback(hwnd, &glfw::glfwOnScroll);
        }
    } // namespace input
} // namespace visus
