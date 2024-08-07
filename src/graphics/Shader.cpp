#include "Shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

namespace visus
{
    namespace graphics
    {
        Shader::Shader(const std::string& vsPath, const std::string& fsPath)
            : _program{0}
        {
            std::string vs = parseShader(vsPath);
            std::string fs = parseShader(fsPath);

            _program = createShaderProgram(vs, fs);
        }

        Shader::~Shader()
        {
            glDeleteShader(_program);
        }

        std::string Shader::parseShader(const std::string& shaderPath)
        {
            std::ifstream file(shaderPath);
            if (!file.is_open())
            {
                std::cout << "Unable to open shader file at: " << shaderPath << '\n';
            }

            std::stringstream sourceBuffer;
            sourceBuffer << file.rdbuf();

            return sourceBuffer.str();
        }

        unsigned int Shader::createShaderProgram(const std::string& vertexShader,
                                                 const std::string& fragmentShader)
        {
            unsigned int program = glCreateProgram();

            // Compile and attach shaders
            unsigned int vs = compileShader(vertexShader, ShaderType::VERTEX);
            glAttachShader(program, vs);

            unsigned int fs = compileShader(fragmentShader, ShaderType::FRAGMENT);
            glAttachShader(program, fs);

            // NOTE(abi): linking ensures that attached shaders get run on the
            // programmable vertex processor.
            glLinkProgram(program);
            glValidateProgram(program);

            // Info log, to check for errors
            GLint logLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0)
            {
                std::vector<char> log(logLength);
                glGetProgramInfoLog(program, logLength, &logLength, log.data());
                std::cout << "[DEBUG] Program's info log:\n" << log.data() << '\n';
            }
            else
            {
                std::cout << "[DEBUG] Program's info log is empty.\n" << std::endl;
            }

            // Clean up
            glDeleteShader(vs);
            glDeleteShader(fs);

            return program;
        }

        unsigned int Shader::compileShader(const std::string& source, ShaderType type)
        {
            unsigned int shaderID =
                glCreateShader(type == ShaderType::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
            const char* src = source.c_str();

            glShaderSource(shaderID, 1, &src, nullptr);
            glCompileShader(shaderID);

            int result;
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
            if (!result)
            {
                int length;
                glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

                char* msg = static_cast<char*>(alloca(sizeof(char) * length));
                glGetShaderInfoLog(shaderID, length, &length, msg);

                switch (type)
                {
                case ShaderType::VERTEX:
                    std::cout << "Failed to compile VERTEX shader\n";
                    break;
                case ShaderType::FRAGMENT:
                    std::cout << "Failed to compile FRAGMENT shader\n";
                    break;
                }
                std::cout << msg << '\n';

                glDeleteShader(shaderID);
                return 0;
            }

            return shaderID;
        }

        unsigned int Shader::getUniformLocation(const std::string& name)
        {
            // Uniform is already cached
            if (_uniformsCache.find(name) != _uniformsCache.end())
            {
                return _uniformsCache[name];
            }

            int location = glGetUniformLocation(_program, name.c_str());
            if (location == -1)
            {
                std::cout << "[WARN]: uniform " << name << " doesn't exist!" << '\n';
            }

            _uniformsCache[name] = location;
            return location;
        }

        void Shader::setUniform1i(const std::string& name, int value)

        {
            glUniform1i(getUniformLocation(name), value);
        }

        void Shader::setUniform1f(const std::string& name, float value)
        {
            glUniform1f(getUniformLocation(name), value);
        }

        void Shader::setUniform3i(const std::string& name, int v1, int v2, int v3)
        {
            glUniform3i(getUniformLocation(name), v1, v2, v3);
        }

        void Shader::setUniform3f(const std::string& name, float v1, float v2, float v3)
        {
            glUniform3f(getUniformLocation(name), v1, v2, v3);
        }

        void Shader::setUniformMat4f(const std::string& name, glm::mat4 matrix)
        {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
        }
    } // namespace graphics
} // namespace visus
