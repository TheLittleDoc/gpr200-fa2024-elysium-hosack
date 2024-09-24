#version 330 core
in vec4 vertexColor;
in vec2 textureCoords;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    vec4 textureColor = texture(uTexture, textureCoords);
    FragColor = textureColor;
}