#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 vertexColor;

uniform float uTime;
uniform float uSpeed;

void main()
{
    vec4 colorT = vec4(aColor.x + abs(tan(uTime)/2.0), aColor.y + abs(tan((uTime) + (aPos.x * 2)))/2.0, aColor.z + abs(tan((uTime) + (aPos.y * 2)))/2.0, 1);
    vec3 aPosT = vec3(aPos.x + abs(sin(uTime * uSpeed))/6.0, aPos.y + abs(cos((uTime * uSpeed) + (aPos.x * 2)))/6.0, 0);
    gl_Position = vec4(aPosT, 1.0);
    vertexColor = aColor * colorT;

}