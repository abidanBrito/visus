#include "InputManager.hpp"
#include "Window.hpp"

InputManager::InputManager(GLFWwindow* hwnd)
{
    // Keyboard interactions
    glfwSetKeyCallback(hwnd, &InputManager::keyCallback);
    glfwSetInputMode(hwnd, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    // Mouse interactions
    glfwSetCursorPosCallback(hwnd, &InputManager::cursorPosCallback);
    glfwSetMouseButtonCallback(hwnd, &InputManager::mouseButtonCallback);
    glfwSetScrollCallback(hwnd, &InputManager::scrollCallback);
}

void InputManager::keyCallback(GLFWwindow* hwnd, [[maybe_unused]] int key,
                               [[maybe_unused]] int scanCode, [[maybe_unused]] int action,
                               [[maybe_unused]] int mods)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
    if (window == NULL || window->getHandle() != hwnd)
    {
        return;
    }

    // TODO(abi): trigger events
}

void InputManager::cursorPosCallback(GLFWwindow* hwnd, [[maybe_unused]] double xPos,
                                     [[maybe_unused]] double yPos)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
    if (window == NULL || window->getHandle() != hwnd)
    {
        return;
    }

    // TODO(abi): trigger events
}

void InputManager::mouseButtonCallback(GLFWwindow* hwnd, [[maybe_unused]] int button,
                                       [[maybe_unused]] int action, [[maybe_unused]] int mods)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
    if (window == NULL || window->getHandle() != hwnd)
    {
        return;
    }

    // TODO(abi): trigger events
}

void InputManager::scrollCallback(GLFWwindow* hwnd, [[maybe_unused]] double xOffset,
                                  [[maybe_unused]] double yOffset)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
    if (window == NULL || window->getHandle() != hwnd)
    {
        return;
    }

    // TODO(abi): trigger events
}
