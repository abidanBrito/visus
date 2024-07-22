#pragma once
#include "Scene.hpp"
#include "../app/App.hpp"

namespace visus
{
    namespace graphics
    {
        Scene::Scene(App* app)
            : _app{app}
        {
            glm::ivec2 viewport{_app->getWindow().getWidth(), _app->getWindow().getHeight()};
            _camera = std::make_unique<Camera>(viewport);
            _volume = std::make_unique<VolumeData>();
        }
    } // namespace graphics
} // namespace visus
