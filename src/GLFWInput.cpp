#include "GLFWInput.hpp"
#include "InputHandler.hpp"
#include "Window.hpp"

namespace visus
{
    namespace input
    {
        void glfwBindEventCallbacks(GLFWwindow* hwnd)
        {
            // Keyboard interactions
            glfwSetKeyCallback(hwnd, &glfwOnKeyPress);
            glfwSetInputMode(hwnd, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

            // Mouse interactions
            glfwSetMouseButtonCallback(hwnd, &glfwOnMouseButtonPress);
            glfwSetCursorPosCallback(hwnd, &glfwOnCursorMove);
            glfwSetScrollCallback(hwnd, &glfwOnScroll);
        }

        void glfwOnKeyPress(GLFWwindow* hwnd, [[maybe_unused]] const int32_t key,
                            [[maybe_unused]] const int32_t scanCode,
                            [[maybe_unused]] const int32_t action,
                            [[maybe_unused]] const int32_t mods)
        {
            Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
            if (window == NULL || window->getHandle() != hwnd)
            {
                return;
            }

            glfwInput.onKeyPress(key, scanCode, action, mods);
        }

        void glfwOnMouseButtonPress(GLFWwindow* hwnd, [[maybe_unused]] const int32_t button,
                                    [[maybe_unused]] const int32_t action,
                                    [[maybe_unused]] const int32_t mods)
        {
            Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
            if (window == NULL || window->getHandle() != hwnd)
            {
                return;
            }

            glfwInput.onMouseButtonPress(button, action, mods);
        }

        void glfwOnCursorMove(GLFWwindow* hwnd, [[maybe_unused]] double xPos,
                              [[maybe_unused]] double yPos)
        {
            Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
            if (window == NULL || window->getHandle() != hwnd)
            {
                return;
            }

            glfwInput.onCursorMove(xPos, yPos);
        }

        void glfwOnScroll(GLFWwindow* hwnd, [[maybe_unused]] double xOffset,
                          [[maybe_unused]] double yOffset)
        {
            Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
            if (window == NULL || window->getHandle() != hwnd)
            {
                return;
            }

            glfwInput.onScroll(xOffset, yOffset);
        }
    } // namespace input
} // namespace visus
