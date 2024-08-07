#include "VBO.hpp"

namespace visus
{
    namespace graphics
    {
        VBO::VBO(std::vector<glm::vec2>& vertices)
        {
            glGenBuffers(1, &_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(),
                         GL_STATIC_DRAW);
        }
    } // namespace graphics
} // namespace visus
