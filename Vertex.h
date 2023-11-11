#ifndef LEARNINGOPENGL_VERTEX_H
#define LEARNINGOPENGL_VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 vertexColor;
    glm::vec2 textureCoordinates;
};

#endif //LEARNINGOPENGL_VERTEX_H
