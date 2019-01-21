#version 330 core
in vec2 TexCoord;

uniform vec4 uColor;

out vec4 color;

uniform sampler2D Texture0;

void main()
{
    color = texture(Texture0, TexCoord) * vec4(uColor);
}
