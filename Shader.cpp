#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

Shader::Shader() {
    handle = 0;
    isLinked = false;
}

bool Shader::compileAndLink(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;
    if (!compileShader(vertexShaderPath, GL_VERTEX_SHADER, vertexShader)) {
        return false;
    }
    if (!compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER, fragmentShader)) {
        return false;
    }
    handle = glCreateProgram();
    glAttachShader(handle, vertexShader);
    glAttachShader(handle, fragmentShader);
    glBindFragDataLocation(handle, 0, "fragmentColor");
    glLinkProgram(handle);
    int status = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &status);
    isLinked = status != GL_FALSE;
    if (!isLinked) {
        std::cout << "Error: linking of shader program failed." << std::endl;
        int infoLogLength = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            std::string infoLog(infoLogLength, ' ');
            glGetProgramInfoLog(handle, infoLogLength, nullptr, &infoLog[0]);
            std::cout << infoLog << std::endl;
        }
    }
    glDetachShader(handle, vertexShader);
    glDetachShader(handle, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (!isLinked) {
        destroy();
    }
    return isLinked;
}

void Shader::use() const {
    glUseProgram(handle);
}

void Shader::setInteger(const std::string &name, int value) const {
    int location = glGetUniformLocation(handle, name.c_str());
    glUniform1i(location, value);
}

void Shader::setMatrix4(const std::string &name, const glm::mat4 &matrix) const {
    int location = glGetUniformLocation(handle, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::dispose() {
    if (isLinked) {
        destroy();
    }
}

bool Shader::readFile(const std::string &shaderPath, std::string &shaderCode) {
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ios::badbit | std::ios::failbit);
    try {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
        return true;
    } catch (const std::ifstream::failure &failure) {
        std::cout << "Error: unable to read shader file \"" << shaderPath << "\".\n" << failure.what() << std::endl;
    }
    return false;
}

bool Shader::compileShader(const std::string &shaderPath, GLenum shaderType, unsigned int &shader) {
    std::string shaderCode;
    if (!readFile(shaderPath, shaderCode)) {
        return false;
    }
    const char *shaderSource = shaderCode.c_str();
    int length = (int) shaderCode.length();
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, &length);
    glCompileShader(shader);
    int status = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        std::cout << "Error: compilation of shader \"" << shaderPath << "\" failed." << std::endl;
        int infoLogLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            std::string infoLog(infoLogLength, ' ');
            glGetShaderInfoLog(shader, infoLogLength, nullptr, &infoLog[0]);
            std::cout << infoLog << std::endl;
        }
        glDeleteShader(shader);
        shader = 0;
        return false;
    }
    return true;
}

void Shader::destroy() {
    glUseProgram(0);
    glDeleteProgram(handle);
    handle = 0;
    isLinked = false;
}
