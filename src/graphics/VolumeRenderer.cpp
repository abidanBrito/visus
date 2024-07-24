#include "VolumeRenderer.hpp"
#include "../app/App.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "IBO.hpp"
#include <iostream>

namespace visus
{
    namespace graphics
    {
        VolumeRenderer::VolumeRenderer(App* app)
            : _app{app}
        {
            setupScreenQuad();
            setupShaders();
            setupDataTexture();

            tfMid = _app->getScene()->getVolume()->getMaximumIntensityValue() / 2.f;
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
            std::vector<unsigned short> indices{
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
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

            // Bind IBO
            _screenQuadIndices->bind();

            // Unbind VAO
            _screenQuad->unbind();

            // IMPORTANT(abi): required by the draw call
            _screenQuadIndicesSize = static_cast<int>(indices.size());

            vertices.clear();
            indices.clear();
        }

        void VolumeRenderer::setupShaders()
        {
            // TODO(abi): set up gradient shader and texture

            // Volume Rendering
            _dvrShader =
                std::make_unique<Shader>("res/shaders/volume.vert", "res/shaders/volume.frag");
        }

        // Create a 3D texture and load volume data into it
        void VolumeRenderer::setupDataTexture()
        {
            // Texture dimensions must match with those of the volume
            GLushort width, height, depth;
            width = _app->getScene()->getVolume()->getDimensions().at(0);
            height = _app->getScene()->getVolume()->getDimensions().at(1);
            depth = _app->getScene()->getVolume()->getDimensions().at(2);

            _volumeTexture = std::make_unique<Texture3D>(width, height, depth, GL_R16F, GL_RED,
                                                         GL_UNSIGNED_SHORT,
                                                         _app->getScene()->getVolume()->getData());
        }

        // Set flat uniforms
        void VolumeRenderer::updateUniforms()
        {
            // Model-Scene-View-Projection matrices
            glm::mat4 modelMat = _app->getScene()->getVolume()->getModelMatrix();
            glm::mat4 sceneMat = _app->getScene()->getSceneMatrix();
            glm::mat4 viewMat = _app->getScene()->getCamera()->getViewMatrix();
            glm::mat4 projectionMat = _app->getScene()->getCamera()->getProjectionMatrix();

            glm::mat4 MSVP = projectionMat * viewMat * sceneMat * modelMat;
            _dvrShader->setUniformMat4f("MSVP", MSVP);
            _dvrShader->setUniformMat4f("inverseMSVP", inverse(MSVP));

            // Ray marching params
            _dvrShader->setUniform1f("tfMid", tfMid);
            _dvrShader->setUniform1f(
                "tfRange", glm::clamp(tfRange, 0.f,
                                      _app->getScene()->getVolume()->getMaximumIntensityValue()));
            _dvrShader->setUniform1f("densityFactor", densityFactor);
            _dvrShader->setUniform1f("marchDistance", marchDistance);

            glActiveTexture(GL_TEXTURE0);
            _volumeTexture->bind();
            _dvrShader->setUniform1i("volumeTexture", 0);
            // _volumeTexture->unbind();
        }

        void VolumeRenderer::render()
        {
            // Enable shader program
            _dvrShader->bind();
            _screenQuad->bind();

            // Pass in data to the shader
            updateUniforms();

            // Render volume
            glDrawElements(GL_TRIANGLES, _screenQuadIndicesSize, GL_UNSIGNED_SHORT, nullptr);

            // Release VAO and shader program
            _screenQuad->unbind();
            _dvrShader->unbind();
        }
    } // namespace graphics
} // namespace visus
