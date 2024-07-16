#include "VAO.hpp"

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

using namespace gl;

namespace visus
{
    namespace graphics
    {
        VAO::VAO()
        {
            glGenVertexArrays(1, &_vertexArray);
        }

        VAO::~VAO()
        {
            glDeleteVertexArrays(1, &_vertexArray);
        }

        void VAO::bind() const
        {
            glBindVertexArray(_vertexArray);
        }

        void VAO::unbind() const
        {
            glBindVertexArray(0);
        }

        void VAO::addVertexBuffer(const VBO& vbo, const VBLayout& layout)
        {
            bind();
            vbo.bind();
            unsigned int offset = 0;
            const auto& elements = layout.getElements();

            for (size_t i = 0; i < elements.size(); ++i)
            {
                const auto& element = elements[i];
                glEnableVertexAttribArray(static_cast<uint32_t>(i));

                // NOTE(abi): we cast to `uintptr_t` first to avoid casting from an integer to a
                // pointer directly.
                glVertexAttribPointer(static_cast<uint32_t>(i), element.count,
                                      static_cast<GLenum>(element.type), element.normalized,
                                      layout.getStride(),
                                      reinterpret_cast<void*>(static_cast<uintptr_t>(offset)));

                offset += element.count * VBElement::getSizeOf(element.type);
            }
        }
    } // namespace graphics
} // namespace visus
