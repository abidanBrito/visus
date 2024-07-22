#pragma once

#include "../core/Window.hpp"
#include "../core/InputManager.hpp"
#include "../graphics/Scene.hpp"
#include "../graphics/VolumeRenderer.hpp"

using namespace visus::graphics;

namespace visus
{
    class App
    {
    private:
        Window _window;
        input::InputManager _input;
        std::unique_ptr<Scene> _scene;
        std::unique_ptr<VolumeRenderer> _renderer;

        void render();
        void update();

    public:
        App();
        void frameloop();
        void clearWindowBuffers(bool color, bool depth, bool stencil);

        inline Window& getWindow()
        {
            return _window;
        }

        inline Scene* getScene() const
        {
            return _scene.get();
        }
    };
} // namespace visus
