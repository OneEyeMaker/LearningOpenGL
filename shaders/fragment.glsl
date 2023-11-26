#version 330 core

struct Material {
    sampler2D backgroundTexture;
    sampler2D foregroundTexture;
    sampler2D specularTexture;
    float specularExponent;
};

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 attenuationCoefficient;
    float innerCutOff;
    float outerCutOff;
};

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec3 vertexColor;
in vec2 textureCoordinates;

out vec4 fragmentColor;

uniform Material material;
uniform Light light;
uniform vec3 viewPosition;

const float threshold = 0.75f;

void main() {
    vec4 backgroundColor = texture(material.backgroundTexture, textureCoordinates);
    vec4 foregroundColor = texture(material.foregroundTexture, textureCoordinates);
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

    vec3 ambientColor = objectColor * light.ambientColor;

    vec3 normal = normalize(vertexNormal);
    vec3 lightDirection = normalize(light.position - vertexPosition);
    float diffuseConstant = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuseColor = objectColor * light.diffuseColor * diffuseConstant;

    vec3 viewDirection = normalize(viewPosition - vertexPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularConstant = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.specularExponent);
    vec3 specularColor = texture(material.specularTexture, textureCoordinates).rgb;
    specularColor *= light.specularColor * specularConstant;

    float lightOffset = dot(lightDirection, normalize(-light.direction));
    float intensity = clamp((lightOffset - light.outerCutOff) / (light.innerCutOff - light.outerCutOff), 0.0f, 1.0f);

    float distance = length(light.position - vertexPosition);
    float attenuation = 1.0f / (light.attenuationCoefficient.x + light.attenuationCoefficient.y * distance +
        light.attenuationCoefficient.z * distance * distance);

    fragmentColor = vec4((ambientColor + (diffuseColor + specularColor) * intensity) * attenuation, 1.0f);
}
