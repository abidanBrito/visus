#pragma once

#include "VBO.hpp"
#include "VBLayout.hpp"

#include <glm/glm.hpp>

namespace visus
{
    namespace graphics
    {
        class VAO
        {
        private:
            uint32_t _vertexArray;

        public:
            VAO();
            ~VAO();

            void addVertexBuffer(const VBO& vb, const VBLayout& layout);

            inline void bind() const
            {
                glBindVertexArray(_vertexArray);
            }

            inline void unbind() const
            {
                glBindVertexArray(0);
            }
        };
    } // namespace graphics
} // namespace visus
