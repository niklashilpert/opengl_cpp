#version 460 core
out vec4 FragColor;

in vec4 fPos;
in vec4 fCenter;
in float fRadiusH;
in float fRadiusV;
in vec4 fColor;

void main()
{
    float scaledDist =
        pow(fPos.x - fCenter.x, 2) / (fRadiusH * fRadiusH) +
        pow(fPos.y - fCenter.y, 2) / (fRadiusV * fRadiusV);
    if (scaledDist > 1) discard;
    FragColor = fColor;
}