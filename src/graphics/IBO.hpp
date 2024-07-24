#pragma once

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <glm/glm.hpp>

#include <vector>

using namespace gl;

namespace visus
{
    namespace graphics
    {
        class IBO
        {
        private:
            unsigned int _indexBuffer;
            unsigned int _count;

        public:
            IBO(std::vector<unsigned short>& indices);
            ~IBO();

            void bind() const
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
            }

            void unbind() const
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
        };
    } // namespace graphics
} // namespace visus
