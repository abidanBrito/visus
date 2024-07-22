#pragma once

#include "VAO.hpp"
#include "VBO.hpp"
#include "IBO.hpp"
#include "Shader.hpp"
// #include "Texture3D.hpp"

#include <glm/glm.hpp>
#include <memory>

namespace visus
{
    class App;

    namespace graphics
    {
        class VolumeRenderer
        {
        private:
            App* _app;

            // Screen quad
            std::unique_ptr<VBO> _screenQuadVertices{nullptr};
            std::unique_ptr<IBO> _screenQuadIndices{nullptr};
            std::unique_ptr<VAO> _screenQuad{nullptr};
            unsigned int _screenQuadIndicesSize;

            // DVR
            std::unique_ptr<Shader> _dvrShader{nullptr};
            // std::shared_ptr<Texture3D> _volumeTexture;

            // TODO(abi): gradient compute shader for normal estimation

            void setupScreenQuad();
            void setupShaders();
            void setupVolumeTexture();
            void setupGradientTexture();
            void updateUniforms();

        public:
            VolumeRenderer(App* app);
            void render();

            // TODO(abi): interactive variables
            // glm::vec4 bgColor{0.f};
            // float marchDistance{0.01f};
            // float densityFactor{1.f};
            // float tfMid;
            // float tdRange{1000.f};
        };
    } // namespace graphics
} // namespace visus
