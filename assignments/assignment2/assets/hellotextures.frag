#version 330 core
in vec4 vertexColor;
in vec2 textureCoords;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    vec4 textureColor = texture(uTexture, textureCoords);
    if(textureColor.a < 0.1)
        discard;
    FragColor = textureColor;
}