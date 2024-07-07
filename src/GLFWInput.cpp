#include "GLFWInput.hpp"
#include "InputHandler.hpp"
#include "Window.hpp"

namespace glfw
{
    bool ownWindowHandle(GLFWwindow* hwnd)
    {
        auto window = static_cast<visus::Window*>(glfwGetWindowUserPointer(hwnd));
        return (window == nullptr || window->getHandle() != hwnd) ? false : true;
    }

    void glfwOnKeyPress(GLFWwindow* hwnd, [[maybe_unused]] const int32_t key,
                        [[maybe_unused]] const int32_t scanCode,
                        [[maybe_unused]] const int32_t action, [[maybe_unused]] const int32_t mods)
    {
        if (!ownWindowHandle(hwnd))
        {
            return;
        }

        visus::input::glfwInput.onKeyPress(key, scanCode, action, mods);
    }

    void glfwOnMouseButtonPress(GLFWwindow* hwnd, [[maybe_unused]] const int32_t button,
                                [[maybe_unused]] const int32_t action,
                                [[maybe_unused]] const int32_t mods)
    {
        if (!ownWindowHandle(hwnd))
        {
            return;
        }

        visus::input::glfwInput.onMouseButtonPress(button, action, mods);
    }

    void glfwOnCursorMove(GLFWwindow* hwnd, [[maybe_unused]] double xPos,
                          [[maybe_unused]] double yPos)
    {
        if (!ownWindowHandle(hwnd))
        {
            return;
        }

        visus::input::glfwInput.onCursorMove(xPos, yPos);
    }

    void glfwOnScroll(GLFWwindow* hwnd, [[maybe_unused]] double xOffset,
                      [[maybe_unused]] double yOffset)
    {
        if (!ownWindowHandle(hwnd))
        {
            return;
        }

        visus::input::glfwInput.onScroll(xOffset, yOffset);
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
