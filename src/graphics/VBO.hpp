#pragma once

#include <vector>

#include <glm/glm.hpp>

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

            void bind() const;
            void unbind() const;
        };
    } // namespace graphics
} // namespace visus
