#pragma once

#include "Camera.hpp"
// #include "VolumeData.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace visus
{
    class App;

    namespace graphics
    {
        class Scene
        {
            App* _app;
            glm::mat4 _sceneMat{1.f};
            std::unique_ptr<Camera> _camera;
            // std::unique_ptr<VolumeData> _volume;

        public:
            Scene(App* app);

            // NOTE(abi): this could be used to modify the entire scene.
            inline glm::mat4 getSceneMatrix() const
            {
                return _sceneMat;
            }

            inline Camera* getCamera() const
            {
                return _camera.get();
            }

            // inline VolumeData* getVolume() const
            // {
            //     return _volume.get();
            // }
        };
    } // namespace graphics
} // namespace visus
