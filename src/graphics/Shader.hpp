#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace visus
{
    namespace graphics
    {
        enum class ShaderType
        {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1
        };

        struct ShaderProgram
        {
            std::string vertexShader;
            std::string fragmentShader;
        };

        class Shader
        {
        private:
            std::string _source;
            uint32_t _program;
            std::unordered_map<std::string, int> _uniformsCache;

            uint32_t getUniformLocation(const std::string& name);
            ShaderProgram parseShader(const std::string& filePath);
            uint32_t createShaderProgram(const std::string& vertexShader,
                                         const std::string& fragmentShader);
            uint32_t compileShader(const std::string& source, uint32_t type);

        public:
            Shader(const std::string& filePath);
            ~Shader();

            void bind() const;
            void unbind() const;

            void setUniform1i(const std::string& name, int32_t value);
            void setUniform3i(const std::string& name, int32_t v1, int32_t v2, int32_t v3);
            void setUniform3i(const std::string& name, glm::ivec3 v);

            void setUniform1f(const std::string& name, float value);
            void setUniform3f(const std::string& name, float v1, float v2, float v3);
            void setUniform3f(const std::string& name, glm::vec3 v);
            void setUniformMat3f(const std::string& name, glm::mat3 matrix);
            void setUniformMat4f(const std::string& name, glm::mat4 matrix);
        };
    } // namespace graphics
} // namespace visus
