#pragma once

#include "VAO.hpp"
#include "VBO.hpp"
#include "IBO.hpp"
#include "Shader.hpp"
#include "Texture3D.hpp"

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
            int _screenQuadIndicesSize;

            // DVR
            std::unique_ptr<Shader> _dvrShader{nullptr};
            std::shared_ptr<Texture3D> _volumeTexture{nullptr};

            void setupScreenQuad();
            void setupShaders();
            void setupDataTexture();

            // TODO(abi): gradient compute shader for normal estimation
            // void setupGradientTexture();

            void updateUniforms();

        public:
            VolumeRenderer(App* app);
            void render();

            // glm::vec4 bgColor{0.f};
            float tfMid{500.f};
            float tfRange{1000.f};
            float densityFactor{1.f};
            float marchDistance{0.01f};
        };
    } // namespace graphics
} // namespace visus
