#include <iostream>
#include <utility>

#include <stb/stb_image.h>

#include "Texture.h"

Texture::Texture(std::string name, std::string imagePath, unsigned int index) :
        name(std::move(name)), imagePath(std::move(imagePath)), index(index) {
    handle = 0;
    isLoaded = false;
}

bool Texture::load() {
    glGenTextures(1, &handle);
    use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width = 0;
    int height = 0;
    int channelsCount = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *imageData = stbi_load(imagePath.c_str(), &width, &height, &channelsCount, 0);
    if (imageData == nullptr) {
        std::cout << "Error: unable to load image file \"" << imagePath << "\"." << std::endl;
        destroy();
        return false;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, channelsCount == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
                 imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imageData);
    isLoaded = true;
    return true;
}

void Texture::attach(const Shader &shader) const {
    shader.setInteger(name, (int) index);
}

void Texture::use() const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture::dispose() {
    if (isLoaded) {
        destroy();
    }
}

void Texture::destroy() {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &handle);
    handle = 0;
    isLoaded = false;
}
