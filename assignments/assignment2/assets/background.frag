#version 330 core
in vec4 vertexColor;
in vec2 textureCoords;

out vec4 FragColor;

uniform sampler2D uTexture2;
uniform sampler2D uTexture3;

void main()
{
    //vec4 textureColor = mix(texture(uTexture, textureCoords), texture(uTexture2, textureCoords), 0.8);
    vec4 textureColor = texture(uTexture2, textureCoords);
    FragColor = textureColor;
}