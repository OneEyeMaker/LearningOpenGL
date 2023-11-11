#include <glad/glad.h>

#include "Mesh.h"

Mesh::Mesh() {
    vertexArray = 0;
    vertexBuffer = 0;
    elementBuffer = 0;
    isLoaded = false;
}

bool Mesh::loadCube() {
    textures = {
            Texture("backgroundTexture", 0),
            Texture("foregroundTexture", 1)
    };
    if (!textures[0].load("resources/textures/background.png") ||
        !textures[1].load("resources/textures/foreground.png")) {
        dispose();
        return false;
    }
    vertices = {
            // front face
            Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec2(0.0f, 0.0f)),
            Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                   glm::vec2(1.0f, 0.0f)),
            Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
                   glm::vec2(1.0f, 1.0f)),
            Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec2(0.0f, 1.0f)),
            // back face
            Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec2(0.0f, 0.0f)),
            Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                   glm::vec2(1.0f, 0.0f)),
            Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
                   glm::vec2(1.0f, 1.0f)),
            Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec2(0.0f, 1.0f)),
            // right face
            Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                   glm::vec2(0.0f, 0.0f)),
            Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec2(1.0f, 0.0f)),
            Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec2(1.0f, 1.0f)),
            Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
                   glm::vec2(0.0f, 1.0f)),
            // left face
            Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                   glm::vec2(0.0f, 0.0f)),
            Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec2(1.0f, 0.0f)),
            Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec2(1.0f, 1.0f)),
            Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
                   glm::vec2(0.0f, 1.0f)),
            // top face
            Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec2(0.0f, 0.0f)),
            Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
                   glm::vec2(1.0f, 0.0f)),
            Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec2(1.0f, 1.0f)),
            Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
                   glm::vec2(0.0f, 1.0f)),
            // bottom face
            Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                   glm::vec2(0.0f, 0.0f)),
            Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec2(1.0f, 0.0f)),
            Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                   glm::vec2(1.0f, 1.0f)),
            Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec2(0.0f, 1.0f))
    };
    indices = {
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7,

            8, 9, 10,
            8, 10, 11,

            12, 13, 14,
            12, 14, 15,

            16, 17, 18,
            16, 18, 19,

            20, 21, 22,
            20, 22, 23
    };
    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &elementBuffer);
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr) (indices.size() * sizeof(unsigned int)), indices.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, vertexColor));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, textureCoordinates));
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
    isLoaded = true;
    return true;
}

void Mesh::setupRendering(const Shader &shader) const {
    for (const auto &texture: textures) {
        texture.setupRendering(shader);
    }
}

void Mesh::draw() const {
    for (const auto &texture: textures) {
        texture.use();
    }
    glBindVertexArray(vertexArray);
    glDrawElements(GL_TRIANGLES, (int) indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh::dispose() {
    for (auto &texture: textures) {
        texture.dispose();
    }
    textures.clear();
    indices.clear();
    vertices.clear();
    if (isLoaded) {
        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &elementBuffer);
        glDeleteVertexArrays(1, &vertexArray);
        vertexBuffer = 0;
        elementBuffer = 0;
        vertexArray = 0;
        isLoaded = false;
    }
}
