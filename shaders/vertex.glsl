#version 330 core

struct Transform {
    mat4 model;
    mat4 view;
    mat4 projection;
    mat3 normal;
};

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTextureCoordinates;

out vec3 vertexPosition;
out vec3 vertexNormal;
out vec3 vertexColor;
out vec2 textureCoordinates;

uniform Transform transform;

void main() {
    vec4 worldPosition = transform.model * vec4(aPosition, 1.0f);
    gl_Position = transform.projection * transform.view * worldPosition;
    vertexPosition = vec3(worldPosition);
    vertexNormal = transform.normal * aNormal;
    vertexColor = aColor;
    textureCoordinates = aTextureCoordinates;
}
