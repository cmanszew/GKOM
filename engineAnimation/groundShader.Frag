#version 330 core
in vec2 TexCoord;

uniform vec4 uColor;

out vec4 color;

uniform sampler2D groundSampler;

void main()
{
    color = texture(groundSampler, TexCoord) * vec4(uColor);
}
