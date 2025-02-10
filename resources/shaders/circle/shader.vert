#version 460 core
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in float inRadius;

out vec3 vColor;
out float vRadius;
out vec4 vCenter;

void main()
{
    gl_Position = vec4(inPosition, 0, 1);
    vRadius = inRadius;
    vColor = inColor;
    vCenter = gl_Position;
}