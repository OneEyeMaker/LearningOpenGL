#ifndef LEARNINGOPENGL_SHADER_H
#define LEARNINGOPENGL_SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader();

    bool compileAndLink(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void use() const;

    void setInteger(const std::string &name, int value) const;

    void setMatrix4(const std::string &name, const glm::mat4 &matrix) const;

    void dispose();

private:
    static bool readFile(const std::string &shaderPath, std::string &shaderCode);

    static bool compileShader(const std::string &shaderPath, GLenum shaderType, unsigned int &shader);

    void destroy();

    unsigned int handle;
    bool isLinked;
};

#endif //LEARNINGOPENGL_SHADER_H
