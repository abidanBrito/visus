#pragma once

#include <functional>

namespace visus
{
    namespace input
    {
        struct InputHandlers
        {
            // Keyboard events
            std::function<void(const int32_t key, const int32_t scanCode, const int32_t action,
                               const int32_t mods)>
                onKeyPress;

            // Mouse events
            std::function<void(const int32_t button, const int32_t action, const int32_t mods)>
                onMouseButtonPress;
            std::function<void(const double xPos, const double yPos)> onCursorMove;
            std::function<void(const double xOffset, const double yOffset)> onScroll;
        };

        extern InputHandlers input;
        extern InputHandlers glfwInput;
    } // namespace input
} // namespace visus
