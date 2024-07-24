#include "IBO.hpp"

namespace visus
{
    namespace graphics
    {
        IBO::IBO(std::vector<unsigned short>& indices)
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
    } // namespace graphics
} // namespace visus
