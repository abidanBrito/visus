#include "Texture3D.hpp"

namespace visus
{
    namespace graphics
    {
        Texture3D::Texture3D(GLushort width, GLushort height, GLushort depth, GLenum internalFormat,
                             GLenum pixelFormat, GLenum type, const void* data)
        {
            // Texture ID
            glGenTextures(1, &_id);

            // Bind texture to the current context
            bind();

            // Linear interpolation for sampling
            // TODO(abi): add switch for nearest neighbour
            // GLenum filterParam = useNearest ? GL_NEAREST : GL_LINEAR;
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Border handling
            // IMPORTANT(abi): extend borders outside [0, 1], no tiling
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

            // Byte-alignment
            // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // Upload texture data to the GPU
            glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, width, height, depth, 0, pixelFormat,
                         type, data);

            // Release texture
            unbind();
        }
    } // namespace graphics
} // namespace visus
