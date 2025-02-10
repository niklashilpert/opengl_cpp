#version 460 core
out vec4 FragColor;

in vec4 fPos;
in vec4 fCenter;
in float fRadius;
in vec3 fColor;

void main()
{
    if (distance(fPos, fCenter) > fRadius) discard;
    FragColor = vec4(fColor, 1);
}