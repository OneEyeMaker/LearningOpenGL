#include <iostream>

#include <stb/stb_image.h>

#include "Texture.h"

Texture::Texture(unsigned int index) : index(index) {
    handle = 0;
    isLoaded = false;
}

bool Texture::load(const std::string &texturePath) {
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
    unsigned char *imageData = stbi_load(texturePath.c_str(), &width, &height, &channelsCount, 0);
    if (imageData == nullptr) {
        std::cout << "Error: unable to load image file \"" << texturePath << "\"." << std::endl;
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
