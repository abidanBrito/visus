#pragma once

#include <string>

namespace visus
{
    struct WindowProperties
    {
        uint32_t width{1280};
        uint32_t height{720};
        std::string title{"Test App"};
        std::string iconPath;

        WindowProperties();

        WindowProperties(const uint32_t _width, const uint32_t _height, const std::string& _title)
            : width(_width),
              height(_height),
              title(_title)
        {
        }

        WindowProperties(const uint32_t _width, const uint32_t _height, const std::string& _title,
                         [[maybe_unused]] const std::string& _iconPath)
            : width(_width),
              height(_height),
              title(_title),
              iconPath(_iconPath)
        {
        }
    };

    class WindowInterface
    {
    public:
        // using EventCallbackFn = std::function<void(Event&)>;

        virtual ~WindowInterface() = default;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        virtual void onUpdate() = 0;

        // Window attributes
        // virtual void setEventCallback(const EventCallbackFn& callback) = 0;
        virtual void setVSync(bool state) = 0;
        virtual bool isVSyncOn() const = 0;

        static WindowInterface* create(const WindowProperties& properties = WindowProperties());
    };

} // namespace visus
