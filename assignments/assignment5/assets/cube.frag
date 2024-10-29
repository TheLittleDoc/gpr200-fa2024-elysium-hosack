#version 330 core
in vec4 vertexColor;
in vec2 textureCoords;
in vec3 normal;

out vec4 FragColor;

uniform sampler2D uTexture;
uniform vec3 lightPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

    vec4 textureColor = texture(uTexture, textureCoords) * vec4(ambient,1.0);
    if(textureColor.a < 0.1)
        discard;
    FragColor = textureColor;
}