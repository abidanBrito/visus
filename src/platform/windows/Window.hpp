#pragma once

#include "../../WindowInterface.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#endif

namespace visus
{
    class Window : public WindowInterface
    {
    private:
        struct WindowDetails
        {
            uint32_t width, height;
            std::string title;
            std::string iconPath;
            bool vSync;
            // EventCallbackFn eventCb;
        };

        GLFWwindow* window;
        WindowDetails details;

        virtual void init(const WindowProperties& properties);
        virtual void shutdown();

    public:
        Window(const WindowProperties& properties);
        virtual ~Window();

        inline uint32_t getWidth() const override
        {
            return details.width;
        }

        inline uint32_t getHeight() const override
        {
            return details.height;
        }

        // void onUpdate() override;

        // Window attributes
        // void setEventCallback(const EventCallbackFn& cb) override
        // {
        //     details.eventCb = cb;
        // }

        void setVSync(bool state) override;
        bool isVSyncOn() const override;
    };
} // namespace visus
