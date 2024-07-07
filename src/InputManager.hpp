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
        class InputManager
        {
        public:
            InputManager(GLFWwindow* hwnd);
        };
    } // namespace input
} // namespace visus
