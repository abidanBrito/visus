#pragma once

#include <vector>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

using namespace gl;

namespace visus
{
    namespace graphics
    {
        struct VBElement
        {
            unsigned int type;
            unsigned int count;
            unsigned char normalized;

            static unsigned int getSizeOf(unsigned int type)
            {
                switch (type)
                {
                case static_cast<unsigned int>(GL_FLOAT):
                    return 4;
                case static_cast<unsigned int>(GL_UNSIGNED_INT):
                    return 4;
                case static_cast<unsigned int>(GL_UNSIGNED_BYTE):
                    return 1;
                }

                return 0;
            }
        };

        class VBLayout
        {
        private:
            std::vector<VBElement> _elements;
            unsigned int _stride;

        public:
            VBLayout()
                : _stride{0}
            {
            }

            inline const std::vector<VBElement> getElements() const
            {
                return _elements;
            }

            inline unsigned int getStride() const
            {
                return _stride;
            }

            template <typename T>
            void push([[maybe_unused]] unsigned int count)
            {
                static_assert(false, "Unsupported type in VBLayout::push");
            }

            template <>
            void push<float>(unsigned int count)
            {
                _elements.push_back({static_cast<unsigned char>(GL_FLOAT), count,
                                     static_cast<unsigned char>(GL_FALSE)});
                _stride += count * VBElement::getSizeOf(static_cast<unsigned int>(GL_FLOAT));
            }

            template <>
            void push<unsigned int>(unsigned int count)
            {
                _elements.push_back({static_cast<unsigned char>(GL_UNSIGNED_INT), count,
                                     static_cast<unsigned char>(GL_FALSE)});
                _stride += count * VBElement::getSizeOf(static_cast<unsigned int>(GL_UNSIGNED_INT));
            }

            template <>
            void push<unsigned char>(unsigned int count)
            {
                _elements.push_back({static_cast<unsigned char>(GL_UNSIGNED_BYTE), count,
                                     static_cast<unsigned char>(GL_TRUE)});
                _stride +=
                    count * VBElement::getSizeOf(static_cast<unsigned int>(GL_UNSIGNED_BYTE));
            }
        };
    } // namespace graphics
} // namespace visus
