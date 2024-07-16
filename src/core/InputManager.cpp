#include "InputManager.hpp"
#include "InputHandler.hpp"
#include "GLFWInput.hpp"

namespace visus
{
    namespace input
    {
        void toggleFullScreen(GLFWwindow* hwnd)
        {
            // Get the primary monitor
            GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

            // Get the monitor's video mode
            const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

            // Set the window to fullscreen
            glfwSetWindowMonitor(hwnd, primaryMonitor, 0, 0, mode->width, mode->height,
                                 mode->refreshRate);
        }

        InputManager::InputManager(GLFWwindow* hwnd)
        {
            // Bind backend event callbacks
            glfwBindEventCallbacks(hwnd);

            // Bind actions to input handlers
            input.onFullscreenPressed = [hwnd](KeyEvent e)
            {
                if (static_cast<int>(e.keyCode) == GLFW_KEY_F
                    && static_cast<int>(e.action) == GLFW_PRESS)
                {
                    toggleFullScreen(hwnd);
                }
            };

            // Bind hardware events to backend handlers (GLFW)
            glfwInput.onKeyPress = [](int32_t key, int32_t scanCode, int32_t action, int32_t mods) {
                input.onFullscreenPressed(KeyEvent{key, scanCode, action, mods});
            };
        }
    } // namespace input
} // namespace visus
