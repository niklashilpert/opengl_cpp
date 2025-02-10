#version 460 core
layout (points) in;
layout (triangle_strip, max_vertices=6) out;

in vec4 vColor[];
in vec2 vPos1[];
in vec2 vPos2[];
in vec2 vOrthogonal[];

out vec4 fColor;

void main() {
    fColor = vColor[0];

    vec2 pos1 = vPos1[0];
    vec2 pos2 = vPos2[0];
    vec2 orth = vOrthogonal[0];

    gl_Position = vec4(pos1 - orth, 0, 1);
    EmitVertex();
    gl_Position = vec4(pos1 + orth, 0, 1);
    EmitVertex();
    gl_Position = vec4(pos2 + orth, 0, 1);
    EmitVertex();
    gl_Position = vec4(pos1 - orth, 0, 1);
    EmitVertex();
    gl_Position = vec4(pos2 - orth, 0, 1);
    EmitVertex();
    gl_Position = vec4(pos2 + orth, 0, 1);
    EmitVertex();

    EndPrimitive();
}