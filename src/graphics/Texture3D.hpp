#pragma once

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

using namespace gl;

namespace visus
{
    namespace graphics
    {
        class Texture3D
        {
        private:
            unsigned int _id;

        public:
            Texture3D(GLushort width, GLushort height, GLushort depth, GLenum internalFormat,
                      GLenum pixelFormat, GLenum type, const void* data, bool useNearest = false);

            inline void bind() const
            {
                glBindTexture(GL_TEXTURE_3D, _id);
            }

            inline void unbind() const
            {
                glBindTexture(GL_TEXTURE_3D, 0);
            }
        };
    } // namespace graphics
} // namespace visus
