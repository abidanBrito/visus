#pragma once

#include <array>
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
        class InputManager
        {
        private:
            bool _fullscreen{false};
            std::array<int, 2> _wndPos{0, 0};
            std::array<int, 2> _wndSize{0, 0};

            void bindActions(GLFWwindow* hwnd);
            void bindToBackend();

            // Actions
            void toggleFullScreen(GLFWwindow* hwnd);

        public:
            InputManager(GLFWwindow* hwnd);
        };
    } // namespace input
} // namespace visus
