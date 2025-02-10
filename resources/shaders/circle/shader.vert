#version 460 core
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in float inRadius;

uniform int screenWidth;
uniform int screenHeight;

out vec4 vColor;
out float vRadius;
out vec4 vCenter;

const mat2 TRANSFORM = mat2(2, 0, 0, -2);

// Transforms absolute pixel coords into relative coords.
vec2 toRelativeCoords(vec2 coords) {
    return vec2(coords.x / screenWidth, coords.y / screenHeight);
}

// Transforms top-left relative coords into GL-coords.
vec2 toGLCoords(vec2 coords) {
    return (TRANSFORM * coords) + vec2(-1, 1);
}

void main()
{
    vec2 transformedPos = toGLCoords(toRelativeCoords(inPosition));

    gl_Position = vec4(transformedPos, 0, 1);
    vRadius = inRadius;
    vColor = inColor;
    vCenter = gl_Position;
}