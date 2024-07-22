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

            inline void bind() const
            {
                glBindTexture(GL_TEXTURE_3D, _id);
            }

            inline void unbind() const
            {
                glBindTexture(GL_TEXTURE_3D, 0);
            }

        public:
            Texture3D(GLsizei width, GLsizei height, GLsizei depth, GLint internalFormat,
                      GLenum pixelFormat, GLenum type, const void* data);
        };
    } // namespace graphics
} // namespace visus
