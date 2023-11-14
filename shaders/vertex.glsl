#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTextureCoordinates;

out vec3 vertexPosition;
out vec3 vertexNormal;
out vec3 vertexColor;
out vec2 textureCoordinates;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
uniform mat3 normalTransform;

void main() {
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(aPosition, 1.0f);
    vertexPosition = vec3(modelTransform * vec4(aPosition, 1.0f));
    vertexNormal = normalTransform * aNormal;
    vertexColor = aColor;
    textureCoordinates = aTextureCoordinates;
}
