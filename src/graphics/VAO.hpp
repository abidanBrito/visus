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

            void bind() const;
            void unbind() const;

            void addVertexBuffer(const VBO& vb, const VBLayout& layout);
        };
    } // namespace graphics
} // namespace visus
