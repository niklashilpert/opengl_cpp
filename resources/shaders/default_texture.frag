#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 textureCoords;

uniform sampler2D texture0;
uniform float alpha_threshold;

void main()
{
    vec4 textureColor = texture(texture0, textureCoords) * vec4(color, 1.0f);
    if (textureColor.w <= alpha_threshold)
        discard;
    FragColor = textureColor;
}