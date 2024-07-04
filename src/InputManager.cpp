#include "InputManager.hpp"
#include "Window.hpp"

InputManager::InputManager(GLFWwindow* hwnd)
{
    // Keyboard interactions
    glfwSetKeyCallback(hwnd, &InputManager::onKeyPress);
    glfwSetInputMode(hwnd, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    // Mouse interactions
    glfwSetMouseButtonCallback(hwnd, &InputManager::onMouseButtonPress);
    glfwSetCursorPosCallback(hwnd, &InputManager::onCursorMove);
    glfwSetScrollCallback(hwnd, &InputManager::onScroll);
}

// void InputManager::bindEventCallbacks(GLFWwindow* hwnd) const
// {
//     // Keyboard interactions
//     glfwSetKeyCallback(hwnd, &InputManager::onKeyPress);
//     glfwSetInputMode(hwnd, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

//     // Mouse interactions
//     glfwSetMouseButtonCallback(hwnd, &InputManager::onMouseButtonPress);
//     glfwSetCursorPosCallback(hwnd, &InputManager::onCursorMove);
//     glfwSetScrollCallback(hwnd, &InputManager::onScroll);
// }

// void InputManager::setCursorMode(GLFWwindow* hwnd, const int32_t mode)
// {
//     glfwSetInputMode(hwnd, GLFW_CURSOR, mode);
// }

// int32_t InputManager::getCursorMode()
// {
//     return m_cursor.mode;
// }

// std::pair<float, float> InputManager::getCursorPosition()
// {
//     return {m_cursor.x, m_cursor.y};
// }

// void InputManager::updateCursorPosition(const float xPos, const float yPos)
// {
//     InputManager::m_cursor.x = xPos;
//     InputManager::m_cursor.y = yPos;
// }

void InputManager::onKeyPress(GLFWwindow* hwnd, [[maybe_unused]] const int32_t key,
                              [[maybe_unused]] const int32_t scanCode,
                              [[maybe_unused]] const int32_t action,
                              [[maybe_unused]] const int32_t mods)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
    if (window == NULL || window->getHandle() != hwnd)
    {
        return;
    }

    // TODO(abi): trigger events
}

void InputManager::onMouseButtonPress(GLFWwindow* hwnd, [[maybe_unused]] const int32_t button,
                                      [[maybe_unused]] const int32_t action,
                                      [[maybe_unused]] const int32_t mods)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
    if (window == NULL || window->getHandle() != hwnd)
    {
        return;
    }

    // TODO(abi): trigger events
}

void InputManager::onCursorMove(GLFWwindow* hwnd, [[maybe_unused]] double xPos,
                                [[maybe_unused]] double yPos)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
    if (window == NULL || window->getHandle() != hwnd)
    {
        return;
    }

    // updateCursorPosition(static_cast<float>(xPos), static_cast<float>(yPos));

    // TODO(abi): trigger events
}

void InputManager::onScroll(GLFWwindow* hwnd, [[maybe_unused]] double xOffset,
                            [[maybe_unused]] double yOffset)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(hwnd));
    if (window == NULL || window->getHandle() != hwnd)
    {
        return;
    }

    // TODO(abi): trigger events
}
