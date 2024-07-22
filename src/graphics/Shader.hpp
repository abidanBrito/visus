#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace visus
{
    namespace graphics
    {
        class Shader
        {
        private:
            enum class ShaderType
            {
                VERTEX,
                FRAGMENT
            };

            unsigned int _program;
            std::unordered_map<std::string, int> _uniformsCache;

            unsigned int getUniformLocation(const std::string& name);
            std::string parseShader(const std::string& shaderPath);
            unsigned int createShaderProgram(const std::string& vertexShader,
                                             const std::string& fragmentShader);
            unsigned int compileShader(const std::string& source, ShaderType type);

        public:
            Shader(const std::string& vsPath, const std::string& fsPath);
            ~Shader();

            void bind() const;
            void unbind() const;

            void setUniform1i(const std::string& name, int value);
            void setUniform3i(const std::string& name, int v1, int v2, int v3);

            void setUniform1f(const std::string& name, float value);
            void setUniform3f(const std::string& name, float v1, float v2, float v3);

            void setUniformMat4f(const std::string& name, glm::mat4 matrix);
        };
    } // namespace graphics
} // namespace visus
