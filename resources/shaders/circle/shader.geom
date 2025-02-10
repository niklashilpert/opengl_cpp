#version 460 core
layout (points) in;
layout (triangle_strip, max_vertices=6) out;

in vec4 vCenter[];
in vec3 vColor[];
in float vRadius[];

out vec4 fCenter;
out vec4 fPos;
out float fRadius;
out vec3 fColor;

void main() {
    fCenter = vCenter[0];
    fColor = vColor[0];
    fRadius = vRadius[0];

    gl_Position = gl_in[0].gl_Position + vec4(vRadius[0], vRadius[0], 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-vRadius[0], vRadius[0], 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-vRadius[0], -vRadius[0], 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(vRadius[0], vRadius[0], 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(vRadius[0], -vRadius[0], 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-vRadius[0], -vRadius[0], 0, 0);
    fPos = gl_Position;
    EmitVertex();

    EndPrimitive();
}