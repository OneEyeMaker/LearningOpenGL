#include <iterator>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>

#include "Mesh.h"

Mesh::Mesh() {
    vertexArray = 0;
    vertexBuffer = 0;
    elementBuffer = 0;
    isLoaded = false;
}

bool Mesh::createTetrahedron() {
    if (textures.empty()) {
        if (!loadTextures()) {
            return false;
        }
    }
    const float sqrt1_3 = glm::inversesqrt(3.0f);
    const float sqrt1_12 = 0.5f * sqrt1_3;
    const float sqrt3_8 = glm::sqrt(0.375f);
    const float sqrt1_24 = 0.5f * glm::inversesqrt(6.0f);
    const float sqrt2 = glm::sqrt(2.0f);
    const float sqrt2_3 = glm::sqrt(2.0f / 3.0f);
    vertices = {
            Vertex(glm::vec3(0.5f, -sqrt1_24, -sqrt1_12), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
                   glm::vec2(0.0f)),
            Vertex(glm::vec3(0.0f, -sqrt1_24, sqrt1_3), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                   glm::vec2(0.0f)),
            Vertex(glm::vec3(-0.5f, -sqrt1_24, -sqrt1_12), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec2(0.0f)),

            Vertex(glm::vec3(0.0f, sqrt3_8, 0.0f), glm::vec3(-sqrt2_3, 1.0f / 3.0f, sqrt2 / 3.0f),
                   glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.5f, 0.5f)),
            Vertex(glm::vec3(-0.5f, -sqrt1_24, -sqrt1_12), glm::vec3(-sqrt2_3, 1.0f / 3.0f, sqrt2 / 3.0f),
                   glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
            Vertex(glm::vec3(0.0f, -sqrt1_24, sqrt1_3), glm::vec3(-sqrt2_3, 1.0f / 3.0f, sqrt2 / 3.0f),
                   glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),

            Vertex(glm::vec3(0.0f, sqrt3_8, 0.0f), glm::vec3(sqrt2_3, 1.0f / 3.0f, sqrt2 / 3.0f),
                   glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.5f, 0.5f)),
            Vertex(glm::vec3(0.0f, -sqrt1_24, sqrt1_3), glm::vec3(sqrt2_3, 1.0f / 3.0f, sqrt2 / 3.0f),
                   glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
            Vertex(glm::vec3(0.5f, -sqrt1_24, -sqrt1_12), glm::vec3(sqrt2_3, 1.0f / 3.0f, sqrt2 / 3.0f),
                   glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),

            Vertex(glm::vec3(0.0f, sqrt3_8, 0.0f), glm::vec3(0.0f, 1.0f / 3.0f, -2.0f * sqrt2 / 3.0f),
                   glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.5f, 0.5f)),
            Vertex(glm::vec3(0.5f, -sqrt1_24, -sqrt1_12), glm::vec3(0.0f, 1.0f / 3.0f, -2.0f * sqrt2 / 3.0f),
                   glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
            Vertex(glm::vec3(-0.5f, -sqrt1_24, -sqrt1_12), glm::vec3(0.0f, 1.0f / 3.0f, -2.0f * sqrt2 / 3.0f),
                   glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f))
    };
    indices = {};
    loadVertexArray();
    isLoaded = true;
    return true;
}

bool Mesh::createCube() {
    if (textures.empty()) {
        if (!loadTextures()) {
            return false;
        }
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
    loadVertexArray();
    isLoaded = true;
    return true;
}

bool Mesh::createOctahedron() {
    if (textures.empty()) {
        if (!loadTextures()) {
            return false;
        }
    }
    const float sqrt1_2 = glm::sqrt(0.5f);
    const float sqrt1_3 = glm::inversesqrt(3.0f);
    vertices = {
            Vertex(glm::vec3(-sqrt1_2, 0.0f, 0.0f), glm::vec3(-sqrt1_3, sqrt1_3, sqrt1_3), glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec2(0.0f, 0.0f)),
            Vertex(glm::vec3(0.0f, 0.0f, sqrt1_2), glm::vec3(-sqrt1_3, sqrt1_3, sqrt1_3), glm::vec3(0.0f, 1.0f, 0.0f),
                   glm::vec2(1.0f, 0.0f)),
            Vertex(glm::vec3(0.0f, sqrt1_2, 0.0f), glm::vec3(-sqrt1_3, sqrt1_3, sqrt1_3), glm::vec3(0.5f, 0.5f, 0.5f),
                   glm::vec2(0.5f, 0.5f)),

            Vertex(glm::vec3(0.0f, 0.0f, sqrt1_2), glm::vec3(sqrt1_3, sqrt1_3, sqrt1_3), glm::vec3(0.0f, 1.0f, 0.0f),
                   glm::vec2(1.0f, 0.0f)),
            Vertex(glm::vec3(sqrt1_2, 0.0f, 0.0f), glm::vec3(sqrt1_3, sqrt1_3, sqrt1_3), glm::vec3(0.0f, 0.0f, 1.0f),
                   glm::vec2(1.0f, 1.0f)),
            Vertex(glm::vec3(0.0f, sqrt1_2, 0.0f), glm::vec3(sqrt1_3, sqrt1_3, sqrt1_3), glm::vec3(0.5f, 0.5f, 0.5f),
                   glm::vec2(0.5f, 0.5f)),

            Vertex(glm::vec3(sqrt1_2, 0.0f, 0.0f), glm::vec3(sqrt1_3, sqrt1_3, -sqrt1_3), glm::vec3(0.0f, 0.0f, 1.0f),
                   glm::vec2(1.0f, 1.0f)),
            Vertex(glm::vec3(0.0f, 0.0f, -sqrt1_2), glm::vec3(sqrt1_3, sqrt1_3, -sqrt1_3), glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec2(0.0f, 1.0f)),
            Vertex(glm::vec3(0.0f, sqrt1_2, 0.0f), glm::vec3(sqrt1_3, sqrt1_3, -sqrt1_3), glm::vec3(0.5f, 0.5f, 0.5f),
                   glm::vec2(0.5f, 0.5f)),

            Vertex(glm::vec3(0.0f, 0.0f, -sqrt1_2), glm::vec3(-sqrt1_3, sqrt1_3, -sqrt1_3), glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec2(0.0f, 1.0f)),
            Vertex(glm::vec3(-sqrt1_2, 0.0f, 0.0f), glm::vec3(-sqrt1_3, sqrt1_3, -sqrt1_3), glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec2(0.0f, 0.0f)),
            Vertex(glm::vec3(0.0f, sqrt1_2, 0.0f), glm::vec3(-sqrt1_3, sqrt1_3, -sqrt1_3), glm::vec3(0.5f, 0.5f, 0.5f),
                   glm::vec2(0.5f, 0.5f)),

            Vertex(glm::vec3(-sqrt1_2, 0.0f, 0.0f), glm::vec3(-sqrt1_3, -sqrt1_3, sqrt1_3), glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec2(0.0f, 0.0f)),
            Vertex(glm::vec3(0.0f, -sqrt1_2, 0.0f), glm::vec3(-sqrt1_3, -sqrt1_3, sqrt1_3), glm::vec3(0.5f, 0.5f, 0.5f),
                   glm::vec2(0.5f, 0.5f)),
            Vertex(glm::vec3(0.0f, 0.0f, sqrt1_2), glm::vec3(-sqrt1_3, -sqrt1_3, sqrt1_3), glm::vec3(0.0f, 1.0f, 0.0f),
                   glm::vec2(1.0f, 0.0f)),

            Vertex(glm::vec3(0.0f, 0.0f, sqrt1_2), glm::vec3(sqrt1_3, -sqrt1_3, sqrt1_3), glm::vec3(0.0f, 1.0f, 0.0f),
                   glm::vec2(1.0f, 0.0f)),
            Vertex(glm::vec3(0.0f, -sqrt1_2, 0.0f), glm::vec3(sqrt1_3, -sqrt1_3, sqrt1_3), glm::vec3(0.5f, 0.5f, 0.5f),
                   glm::vec2(0.5f, 0.5f)),
            Vertex(glm::vec3(sqrt1_2, 0.0f, 0.0f), glm::vec3(sqrt1_3, -sqrt1_3, sqrt1_3), glm::vec3(0.0f, 0.0f, 1.0f),
                   glm::vec2(1.0f, 1.0f)),

            Vertex(glm::vec3(sqrt1_2, 0.0f, 0.0f), glm::vec3(sqrt1_3, -sqrt1_3, -sqrt1_3), glm::vec3(0.0f, 0.0f, 1.0f),
                   glm::vec2(1.0f, 1.0f)),
            Vertex(glm::vec3(0.0f, -sqrt1_2, 0.0f), glm::vec3(sqrt1_3, -sqrt1_3, -sqrt1_3), glm::vec3(0.5f, 0.5f, 0.5f),
                   glm::vec2(0.5f, 0.5f)),
            Vertex(glm::vec3(0.0f, 0.0f, -sqrt1_2), glm::vec3(sqrt1_3, -sqrt1_3, -sqrt1_3), glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec2(0.0f, 1.0f)),

            Vertex(glm::vec3(0.0f, 0.0f, -sqrt1_2), glm::vec3(-sqrt1_3, -sqrt1_3, -sqrt1_3),
                   glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec2(0.0f, 1.0f)),
            Vertex(glm::vec3(0.0f, -sqrt1_2, 0.0f), glm::vec3(-sqrt1_3, -sqrt1_3, -sqrt1_3),
                   glm::vec3(0.5f, 0.5f, 0.5f),
                   glm::vec2(0.5f, 0.5f)),
            Vertex(glm::vec3(-sqrt1_2, 0.0f, 0.0f), glm::vec3(-sqrt1_3, -sqrt1_3, -sqrt1_3),
                   glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec2(0.0f, 0.0f))
    };
    indices = {};
    loadVertexArray();
    isLoaded = true;
    return true;
}

bool Mesh::createTorus() {
    if (textures.empty()) {
        if (!loadTextures()) {
            return false;
        }
    }
    vertices = {};
    indices = {};
    const float largeRadius = 0.75f;
    const float smallRadius = 0.25f;
    const int largeSegments = 16;
    const int smallSegments = 16;
    const float largeAngleShift = 2.0f * glm::pi<float>() / (float) largeSegments;
    const float smallAngleShift = 2.0f * glm::pi<float>() / (float) smallSegments;
    const glm::vec3 redColor(1.0f, 0.0f, 0.0f);
    const glm::vec3 greenColor(0.0f, 1.0f, 0.0f);
    const glm::vec3 blueColor(0.0f, 0.0f, 1.0f);
    const glm::vec3 yellowColor(1.0f, 1.0f, 0.0f);
    for (int largeIndex = 0; largeIndex <= largeSegments; ++largeIndex) {
        float largeAngle = largeAngleShift * (float) largeIndex;
        float largeOffset = (float) largeIndex / (float) largeSegments * 4.0f;
        glm::vec3 color;
        if (largeOffset < 1.0f) {
            color = glm::mix(redColor, greenColor, largeOffset);
        } else if (largeOffset < 2.0f) {
            color = glm::mix(greenColor, blueColor, largeOffset - 1.0f);
        } else if (largeOffset < 3.0f) {
            color = glm::mix(blueColor, yellowColor, largeOffset - 2.0f);
        } else {
            color = glm::mix(yellowColor, redColor, largeOffset - 3.0f);
        }
        for (int smallIndex = 0; smallIndex <= smallSegments; ++smallIndex) {
            float smallAngle = smallAngleShift * (float) smallIndex;
            float smallOffset = (float) smallIndex / (float) smallSegments * 2.0f;
            glm::vec3 position(
                    (largeRadius + smallRadius * glm::cos(smallAngle)) * glm::cos(largeAngle),
                    smallRadius * glm::sin(smallAngle),
                    (largeRadius + smallRadius * glm::cos(smallAngle)) * glm::sin(largeAngle)
            );
            glm::vec3 normal(
                    smallRadius * glm::cos(smallAngle) * glm::cos(largeAngle),
                    smallRadius * glm::sin(smallAngle),
                    smallRadius * glm::cos(smallAngle) * glm::sin(largeAngle)
            );
            vertices.emplace_back(position, glm::normalize(normal), color,
                                  glm::vec2(largeOffset, smallOffset));
            if (smallIndex == smallSegments || largeIndex == largeSegments) {
                continue;
            }
            indices.push_back(largeIndex * (smallSegments + 1) + smallIndex);
            indices.push_back(largeIndex * (smallSegments + 1) + smallIndex + 1);
            indices.push_back((largeIndex + 1) * (smallSegments + 1) + smallIndex + 1);
            indices.push_back(largeIndex * (smallSegments + 1) + smallIndex);
            indices.push_back((largeIndex + 1) * (smallSegments + 1) + smallIndex + 1);
            indices.push_back((largeIndex + 1) * (smallSegments + 1) + smallIndex);
        }
    }
    loadVertexArray();
    isLoaded = true;
    return true;
}

void Mesh::useTexturesOf(const Mesh &mesh) {
    textures.clear();
    std::copy(mesh.textures.begin(), mesh.textures.end(), std::back_inserter(textures));
}

void Mesh::attachTextures(const Shader &shader) const {
    for (const auto &texture: textures) {
        texture.attach(shader);
    }
}

void Mesh::drawArrays() const {
    for (const auto &texture: textures) {
        texture.use();
    }
    glBindVertexArray(vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, (int) vertices.size());
    glBindVertexArray(0);
}

void Mesh::drawElements() const {
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

bool Mesh::loadTextures() {
    textures = {
            Texture("material.backgroundTexture", "resources/textures/background.png", 0),
            Texture("material.foregroundTexture", "resources/textures/foreground.png", 1),
            Texture("material.specularTexture", "resources/textures/specular.png", 2)
    };
    for (auto &texture: textures) {
        if (!texture.load()) {
            dispose();
            return false;
        }
    }
    return true;
}

void Mesh::loadVertexArray() {
    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);
    if (!indices.empty()) {
        glGenBuffers(1, &elementBuffer);
    }
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);
    if (!indices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr) (indices.size() * sizeof(unsigned int)), indices.data(),
                     GL_STATIC_DRAW);
    }
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, vertexColor));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, textureCoordinates));
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
}
