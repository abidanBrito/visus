#include "IBO.hpp"

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

using namespace gl;

namespace visus
{
    namespace graphics
    {
        IBO::IBO(std::vector<unsigned int>& indices)
            : _count(static_cast<unsigned int>(indices.size()))
        {
            glGenBuffers(1, &_indexBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]),
                         indices.data(), GL_STATIC_DRAW);
        }

        IBO::~IBO()
        {
            glDeleteBuffers(1, &_indexBuffer);
        }

        void IBO::bind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
        }

        void IBO::unbind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    } // namespace graphics
} // namespace visus
