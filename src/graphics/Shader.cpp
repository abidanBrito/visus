#include "Shader.hpp"

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

#include <fstream>
#include <sstream>
#include <iostream>

using namespace gl;

namespace visus
{
    namespace graphics
    {
        Shader::Shader(const std::string& filePath)
            : _source{filePath},
              _program{0}
        {
            ShaderProgram source = parseShader(filePath);
            _program = createShaderProgram(source.vertexShader, source.fragmentShader);
        }

        Shader::~Shader()
        {
            glDeleteShader(_program);
        }

        void Shader::bind() const
        {
            glUseProgram(_program);
        }

        void Shader::unbind() const
        {
            glUseProgram(0);
        }

        ShaderProgram Shader::parseShader(const std::string& filePath)
        {
            std::ifstream stream(filePath);
            std::string line;
            std::stringstream ss[2];

            ShaderType type = ShaderType::NONE;

            while (getline(stream, line))
            {
                if (line.find("#shader") != std::string::npos)
                {
                    if (line.find("vertex") != std::string::npos)
                    {
                        type = ShaderType::VERTEX;
                    }
                    else if (line.find("fragment") != std::string::npos)
                    {
                        type = ShaderType::FRAGMENT;
                    }
                }
                else
                {
                    ss[(int)type] << line << "\n";
                }
            }

            return {ss[0].str(), ss[1].str()};
        }

        uint32_t Shader::createShaderProgram(const std::string& vertexShader,
                                             const std::string& fragmentShader)
        {
            uint32_t program = static_cast<uint32_t>(glCreateProgram());

            // Compile and attach shaders
            unsigned int vs =
                compileShader(vertexShader, static_cast<unsigned int>(GL_VERTEX_SHADER));
            glAttachShader(program, vs);

            unsigned int fs =
                compileShader(fragmentShader, static_cast<unsigned int>(GL_FRAGMENT_SHADER));
            glAttachShader(program, fs);

            // NOTE(abi): linking ensures that attached shaders get run on the
            // programmable vertex processor.
            glLinkProgram(program);
            glValidateProgram(program);

            // Clean up
            glDeleteShader(vs);
            glDeleteShader(fs);

            return program;
        }

        // TODO(abi): exception handling.
        uint32_t Shader::compileShader(const std::string& source, uint32_t type)
        {
            unsigned int shaderID = glCreateShader(static_cast<GLenum>(type));
            const char* src = source.c_str();

            glShaderSource(shaderID, 1, &src, nullptr);
            glCompileShader(shaderID);

            int result;
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

            if (result)
            {
                int length;
                glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

                char* msg = (char*)alloca(sizeof(char) * length);
                glGetShaderInfoLog(shaderID, length, &length, msg);

                switch (type)
                {
                case static_cast<uint32_t>(GL_VERTEX_SHADER):
                    std::cout << "Failed to compile VERTEX shader\n";
                    break;
                case static_cast<uint32_t>(GL_FRAGMENT_SHADER):
                    std::cout << "Failed to compile FRAGMENT shader\n";
                    break;
                }
                std::cout << msg << '\n';

                glDeleteShader(shaderID);
                return 0;
            }

            return static_cast<uint32_t>(shaderID);
        }

        uint32_t Shader::getUniformLocation(const std::string& name)
        {
            // Uniform is already cached
            if (_uniformsCache.find(name) != _uniformsCache.end())
            {
                return static_cast<uint32_t>(_uniformsCache[name]);
            }

            int location = glGetUniformLocation(_program, name.c_str());
            if (location != -1)
            {
                _uniformsCache[name] = location;
            }

            return location;
        }

        void Shader::setUniform1i(const std::string& name, int32_t value)

        {
            glUniform1i(getUniformLocation(name), value);
        }

        void Shader::setUniform1f(const std::string& name, float value)
        {
            glUniform1f(getUniformLocation(name), value);
        }

        void Shader::setUniform3i(const std::string& name, int32_t v1, int32_t v2, int32_t v3)
        {
            glUniform3i(getUniformLocation(name), v1, v2, v3);
        }

        void Shader::setUniform3i(const std::string& name, glm::ivec3 v)
        {
            glUniform3iv(getUniformLocation(name), 1, &v[0]);
        }

        void Shader::setUniform3f(const std::string& name, float v1, float v2, float v3)
        {
            glUniform3f(getUniformLocation(name), v1, v2, v3);
        }

        void Shader::setUniform3f(const std::string& name, glm::vec3 v)
        {
            glUniform3fv(getUniformLocation(name), 1, &v[0]);
        }

        void Shader::setUniformMat3f(const std::string& name, glm::mat3 matrix)
        {
            glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
        }

        void Shader::setUniformMat4f(const std::string& name, glm::mat4 matrix)
        {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
        }

    } // namespace graphics
} // namespace visus
