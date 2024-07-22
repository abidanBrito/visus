#include "VolumeRenderer.hpp"
#include "../app/App.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "IBO.hpp"
#include "Shader.hpp"

namespace visus
{
    namespace graphics
    {
        VolumeRenderer::VolumeRenderer(App* app)
            : _app{app}
        {
            setupScreenQuad();
            setupShaders();
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
            std::vector<uint32_t> indices{
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
            _screenQuadIndicesSize = static_cast<unsigned int>(indices.size());

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

        void VolumeRenderer::render()
        {
            // Enable shader program
            _dvrShader->bind();
            _screenQuad->bind();

            // Pass in data to the shader
            // updateUniforms();

            // Render volume
            glDrawElements(GL_TRIANGLES, _screenQuadIndicesSize, GL_UNSIGNED_INT, nullptr);

            // Release VAO and shader program
            _screenQuad->unbind();
            _dvrShader->unbind();
        }

        void VolumeRenderer::updateUniforms()
        {
            // TODO(abi): add model matrix
            glm::mat4 sceneMatrix = _app->getScene()->getSceneMatrix();
            // glm::mat4 modelMatrix = _app->getScene()->getVolume()->getModelMatrix();
            glm::mat4 viewMatrix = _app->getScene()->getCamera()->getViewMatrix();
            glm::mat4 projectionMatrix = _app->getScene()->getCamera()->getProjectionMatrix();

            // P * V * S * M
            glm::mat4 modelViewProjectionMat = projectionMatrix * viewMatrix * sceneMatrix;

            _dvrShader->setUniformMat4f("MVP", modelViewProjectionMat);
        }
    } // namespace graphics
} // namespace visus
