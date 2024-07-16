#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace visus
{
    namespace graphics
    {
        struct VertexData
        {
            glm::vec3 position;
            glm::vec2 texCoords;
        };

        class VBO
        {
        private:
            uint32_t _vbo;

        public:
            VBO(std::vector<VertexData>& vertices);
            VBO(std::vector<glm::vec3>& vertices);

            void bind() const;
            void unbind() const;
        };
    } // namespace graphics
} // namespace visus
