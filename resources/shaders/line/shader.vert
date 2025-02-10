#version 460 core
layout (location = 0) in vec2 inPosition1;
layout (location = 1) in vec2 inPosition2;
layout (location = 2) in vec4 inColor;
layout (location = 3) in float inWidth;

uniform int screenWidth;
uniform int screenHeight;

out vec2 vPos1;
out vec2 vPos2;
out vec2 vOrthogonal;
out vec4 vColor;

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
    vec2 direction = inPosition2 - inPosition1;
    vec2 orth = normalize(vec2(-direction.y, direction.x)) * inWidth;
    vec2 sampleCornerPos = inPosition1 + orth;

    vPos1 = toGLCoords(toRelativeCoords(inPosition1));
    vPos2 = toGLCoords(toRelativeCoords(inPosition2));
    vec2 convertedCornerPos = toGLCoords(toRelativeCoords(sampleCornerPos));
    vOrthogonal = vPos1 - convertedCornerPos;

    vColor = inColor;

    // The geometry shader ignores the vertex itself.
    // This is why we don't set the vertex position here.
}