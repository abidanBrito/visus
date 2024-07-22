#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace visus
{
    namespace graphics
    {
        class IBO
        {
        private:
            uint32_t _indexBuffer;
            unsigned int _count;

        public:
            IBO(std::vector<unsigned int>& indices);
            ~IBO();

            void bind() const;
            void unbind() const;
        };
    } // namespace graphics
} // namespace visus
