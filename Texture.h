#ifndef LEARNINGOPENGL_TEXTURE_H
#define LEARNINGOPENGL_TEXTURE_H

#include <glad/glad.h>

#include <string>

class Texture {
public:
    explicit Texture(unsigned int index = 0);

    bool load(const std::string &texturePath);

    void use() const;

    void dispose();

private:
    void destroy();

    unsigned int handle;
    unsigned int index;
    bool isLoaded;
};

#endif //LEARNINGOPENGL_TEXTURE_H
