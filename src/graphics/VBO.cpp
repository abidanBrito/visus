#include "VBO.hpp"

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

using namespace gl;

namespace visus
{
    namespace graphics
    {
        VBO::VBO(std::vector<VertexData>& vertices)
        {
            glGenBuffers(1, &_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), vertices.data(),
                         GL_STATIC_DRAW);
        }

        VBO::VBO(std::vector<glm::vec3>& vertices)
        {
            glGenBuffers(1, &_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0],
                         GL_STATIC_DRAW);
        }

        void VBO::bind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        }

        void VBO::unbind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    } // namespace graphics
} // namespace visus
