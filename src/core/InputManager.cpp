#include "InputManager.hpp"
#include "InputHandler.hpp"
#include "GLFWInput.hpp"
#include "../app/App.hpp"

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM <glbinding/gl/gl.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

namespace visus
{
    namespace input
    {
        InputManager::InputManager(GLFWwindow* hwnd)
        {
            // Bind backend event callbacks
            glfwBindEventCallbacks(hwnd);

            bindActions(hwnd);
            bindToBackend();
        }

        void InputManager::bindActions(GLFWwindow* hwnd)
        {
            // Bind actions to input handlers
            input.onKeyPressed = [hwnd, this](KeyEvent e)
            {
                if (static_cast<int>(e.keyCode) == GLFW_KEY_F
                    && static_cast<int>(e.action) == GLFW_PRESS)
                {
                    toggleFullScreen(hwnd);
                }
                else if (static_cast<int>(e.keyCode) == GLFW_KEY_Q
                         && static_cast<int>(e.action) == GLFW_PRESS)
                {
                    // NOTE(abi): the OS releases all memory, so I reckon this is fine.
                    exit(EXIT_SUCCESS);
                }
            };

            input.onCursorMoved = [hwnd](MCursorMoveEvent e)
            {
                // NOTE(abi): we don't want to modify the 3D view while using the GUI (bad UX!).
                if (App* app = static_cast<App*>(glfwGetWindowUserPointer(hwnd));
                    app && !ImGui::GetIO().WantCaptureMouse)
                {
                    app->getScene()->getCamera()->onCursorMove(e.xPos, e.yPos);
                }
            };

            input.onScrolled = [hwnd](MScrollEvent e)
            {
                if (App* app = static_cast<App*>(glfwGetWindowUserPointer(hwnd));
                    app && !ImGui::GetIO().WantCaptureMouse)
                {
                    app->getScene()->getCamera()->onScroll(e.xOffset, e.yOffset);
                }
            };

            input.onMButtonPressed = [hwnd](MButtonPressEvent e)
            {
                if (App* app = static_cast<App*>(glfwGetWindowUserPointer(hwnd));
                    app && !ImGui::GetIO().WantCaptureMouse)
                {
                    app->getScene()->getCamera()->onMButtonPress(e.button, e.action);
                }
            };
        }

        void InputManager::bindToBackend()
        {
            // Bind handlers to backend handlers (hardware events)
            glfwInput.onKeyPress = [](int32_t key, int32_t scanCode, int32_t action, int32_t mods) {
                input.onKeyPressed(KeyEvent{key, scanCode, action, mods});
            };

            glfwInput.onCursorMove = [](const double xPos, const double yPos) {
                input.onCursorMoved(MCursorMoveEvent{xPos, yPos});
            };

            glfwInput.onScroll = [](const double xOffset, const double yOffset) {
                input.onScrolled(MScrollEvent{xOffset, yOffset});
            };

            glfwInput.onMouseButtonPress = [](const int32_t button, const int32_t action,
                                              const int32_t mods) {
                input.onMButtonPressed(MButtonPressEvent{button, action, mods});
            };
        }

        void InputManager::toggleFullScreen(GLFWwindow* hwnd)
        {
            if (!_fullscreen)
            {
                // Cache window position and size
                glfwGetWindowPos(hwnd, &_wndPos[0], &_wndPos[1]);
                glfwGetWindowSize(hwnd, &_wndSize[0], &_wndSize[1]);

                // Get the primary monitor
                GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

                // Get the monitor's video mode
                const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

                // Set the window to fullscreen
                glfwSetWindowMonitor(hwnd, primaryMonitor, 0, 0, mode->width, mode->height,
                                     mode->refreshRate);
            }
            else
            {
                // Restore the window
                glfwSetWindowMonitor(hwnd, nullptr, _wndPos[0], _wndPos[1], _wndSize[0],
                                     _wndSize[1], 0);
            }

            _fullscreen ^= true;
        }

        // // BUG(abi): kills the window, but not the running process
        // void InputManager::exit(GLFWwindow* hwnd) const
        // {
        //     glfwDestroyWindow(hwnd);
        //     glfwTerminate();
        // }
    } // namespace input
} // namespace visus
