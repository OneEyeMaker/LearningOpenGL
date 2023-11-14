#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec3 vertexColor;
in vec2 textureCoordinates;

out vec4 fragmentColor;

uniform sampler2D backgroundTexture;
uniform sampler2D foregroundTexture;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor;

const float threshold = 0.75f;

void main() {
    vec4 backgroundColor = texture(backgroundTexture, textureCoordinates);
    vec4 foregroundColor = texture(foregroundTexture, textureCoordinates);
    vec4 mixedColor;
    if (foregroundColor.a >= threshold && backgroundColor.a >= threshold) {
        mixedColor = mix(foregroundColor, backgroundColor, 0.5f);
    } else {
        mixedColor = mix(foregroundColor, backgroundColor, backgroundColor.a);
    }
    vec3 objectColor;
    if (mixedColor.a >= threshold) {
        objectColor = mixedColor.rgb;
    } else {
        objectColor = mix(vertexColor, mixedColor.rgb, mixedColor.a);
    }

    float ambientConstant = 0.125f;

    vec3 normal = normalize(vertexNormal);
    vec3 lightDirection = normalize(lightPosition - vertexPosition);
    float diffuseConstant = max(dot(normal, lightDirection), 0.0f);

    vec3 viewDirection = normalize(viewPosition - vertexPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularConstant = 0.75f * pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);

    fragmentColor = vec4((ambientConstant + diffuseConstant + specularConstant) * lightColor * objectColor, 1.0f);
}
