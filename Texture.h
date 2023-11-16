#ifndef LEARNINGOPENGL_TEXTURE_H
#define LEARNINGOPENGL_TEXTURE_H

#include <string>

#include <glad/glad.h>

#include "Shader.h"

class Texture {
public:
    explicit Texture(std::string name, unsigned int index = 0);

    bool load(const std::string &texturePath);

    void attach(const Shader &shader) const;

    void use() const;

    void dispose();

private:
    void destroy();

    std::string name;
    unsigned int handle;
    unsigned int index;
    bool isLoaded;
};

#endif //LEARNINGOPENGL_TEXTURE_H
