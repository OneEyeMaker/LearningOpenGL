#version 330 core

in vec3 vertexColor;
in vec2 textureCoordinates;

out vec4 fragmentColor;

uniform sampler2D backgroundTexture;
uniform sampler2D foregroundTexture;

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
    if (mixedColor.a >= threshold) {
        fragmentColor = vec4(mixedColor.rgb, 1.0f);
    } else {
        fragmentColor = vec4(mix(vertexColor, mixedColor.rgb, mixedColor.a), 1.0f);
    }
}
