#version 460 core
layout (points) in;
layout (triangle_strip, max_vertices=6) out;

in vec4 vCenter[];
in vec4 vColor[];
in float vRadius[];

out vec4 fCenter;
out vec4 fColor;
out float fRadiusH;
out float fRadiusV;
out vec4 fPos;

uniform int screenWidth;
uniform int screenHeight;

void main() {
    fCenter = vCenter[0];
    fColor = vColor[0];

    fRadiusH = vRadius[0] / screenWidth;
    fRadiusV = vRadius[0] / screenHeight;

    gl_Position = gl_in[0].gl_Position + vec4(fRadiusH, fRadiusV, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-fRadiusH, fRadiusV, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-fRadiusH, -fRadiusV, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(fRadiusH, fRadiusV, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(fRadiusH, -fRadiusV, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-fRadiusH, -fRadiusV, 0, 0);
    fPos = gl_Position;
    EmitVertex();

    EndPrimitive();
}