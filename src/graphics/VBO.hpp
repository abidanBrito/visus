#pragma once

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

#include <vector>

#include <glm/glm.hpp>

using namespace gl;

namespace visus
{
    namespace graphics
    {
        class VBO
        {
        private:
            unsigned int _vbo;

        public:
            VBO(std::vector<glm::vec2>& vertices);

            inline void bind() const
            {
                glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            }

            inline void unbind() const
            {
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }
        };
    } // namespace graphics
} // namespace visus
