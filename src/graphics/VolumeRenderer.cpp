#include "VolumeRenderer.hpp"
#include "../app/App.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "IBO.hpp"

namespace visus
{
    namespace graphics
    {
        VolumeRenderer::VolumeRenderer(App* app)
            : _app{app}
        {
            setupScreenQuad();
            setupShaders();
            setupVolumeTexture();

            // TODO(abi): get mid value from the volume
            // tfMid = _app->getScene()->getVolume()->getMaximumIntensityValue() / 2.f;
        }

        void VolumeRenderer::setupScreenQuad()
        {
            // Coordinates (per vertex)
            std::vector<glm::vec2> vertices{
                glm::vec2(-1.f, -1.f), // Top-left
                glm::vec2(1.f, -1.f),  // Bottom-left
                glm::vec2(1.f, 1.f),   // Top-right
                glm::vec2(-1.f, 1.f),  // Bottom-right
            };

            // Indices (per triangle)
            std::vector<unsigned char> indices{
                0, 1, 2, // Triangle #1
                2, 3, 0  // Triangle #2
            };

            // Create and populate VBO with vertex coordinates
            _screenQuadVertices = std::make_unique<VBO>(vertices);

            // Create and populate IBO with element indices
            _screenQuadIndices = std::make_unique<IBO>(indices);

            // Create VAO
            _screenQuad = std::make_unique<VAO>();
            _screenQuad->bind();

            // Bind VBO
            _screenQuadVertices->bind();

            // Add VBO to VAO
            // BUG(abi): there's something off here...
            // VBLayout layout;
            // layout.push<float>(2);
            // _screenQuad->addVertexBuffer(*_screenQuadVertices, layout);

            // HACK(abi): for now, let's make the OpenGL calls ourselves.
            glEnableVertexAttribArray(0);

            // Generic vertex attribute data definition
            // Params: (index, size, type, normalized, stride, pointer)
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

            // Bind IBO
            _screenQuadIndices->bind();

            // Unbind VAO
            _screenQuad->unbind();

            // IMPORTANT(abi): required by the draw call
            _screenQuadIndicesSize = static_cast<unsigned int>(indices.size());

            vertices.clear();
            indices.clear();
        }

        void VolumeRenderer::setupShaders()
        {
            // Volume Rendering
            _dvrShader =
                std::make_unique<Shader>("res/shaders/volume.vert", "res/shaders/volume.frag");

            // TODO(abi): set up gradient shader and texture
        }

        void VolumeRenderer::setupVolumeTexture()
        {
            // NOTE(abi): texture dimensions must match those of the volume
            unsigned short width, height, depth;
            width = _app->getScene()->getVolume()->getDimensions().at(0);
            height = _app->getScene()->getVolume()->getDimensions().at(1);
            depth = _app->getScene()->getVolume()->getDimensions().at(2);

            // Create / set up the 3D texture and load the volume data into it
            _volumeTexture = std::make_unique<Texture3D>(width, height, depth, GL_R16F, GL_RED,
                                                         GL_UNSIGNED_SHORT,
                                                         _app->getScene()->getVolume()->getData());

            // Bind it to texture unit 0
            glActiveTexture(GL_TEXTURE0);
            _volumeTexture->bind();
        }

        // Set flat uniforms
        void VolumeRenderer::updateUniforms()
        {
            // NOTE(abi): we could transform the scene as a whole via. By default though,
            // `sceneMat` is an identity matrix.
            glm::mat4 sceneMat = _app->getScene()->getSceneMatrix();

            // MVP
            glm::mat4 modelMat = _app->getScene()->getVolume()->getModelMatrix();
            glm::mat4 viewMat = _app->getScene()->getCamera()->getViewMatrix();
            glm::mat4 projectionMat = _app->getScene()->getCamera()->getProjectionMatrix();

            glm::mat4 msvpMat = projectionMat * viewMat * sceneMat * modelMat;

            // _dvrShader->setUniformMat4f("MVP", msvpMat);
            _dvrShader->setUniformMat4f("invMVP", glm::inverse(msvpMat));

            // TODO(abi): don't hardcode these...
            // DVR params
            _dvrShader->setUniform1f("tfMid", 1482.f);
            _dvrShader->setUniform1f("tfRange", 1000.f);
            _dvrShader->setUniform1f("marchStep", 0.01f);
            _dvrShader->setUniform1f("densityFactor", 1.f);

            // _dvrShader->setUniform1f(
            // "tfRange", glm::clamp(tfRange, 0.f,
            // _app->getScene()->getVolume()->getMaximumIntensityValue()));

            // Volume texture
            _dvrShader->setUniform1i("volumeTexture", 0);
            // _volumeTexture->unbind();

            // TODO(abi): add gradient texture
        }

        void VolumeRenderer::render()
        {
            // Enable shader program
            _dvrShader->bind();

            // Pass in data to the shader
            updateUniforms();

            // Enable VAO
            _screenQuad->bind();

            // Render volume
            glDrawElements(GL_TRIANGLES, _screenQuadIndicesSize, GL_UNSIGNED_BYTE, nullptr);

            // Release VAO and shader program
            _screenQuad->unbind();
            _dvrShader->unbind();
        }
    } // namespace graphics
} // namespace visus
