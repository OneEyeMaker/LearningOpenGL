#ifndef LEARNINGOPENGL_MESH_H
#define LEARNINGOPENGL_MESH_H

#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"

class Mesh {
public:
    Mesh();

    bool loadCube();

    bool loadOctahedron();

    void setupRendering(const Shader &shader) const;

    void drawArrays() const;

    void drawElements() const;

    void dispose();

private:
    void loadVertexArray();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int vertexArray;
    unsigned int vertexBuffer;
    unsigned int elementBuffer;
    bool isLoaded;
};

#endif //LEARNINGOPENGL_MESH_H
