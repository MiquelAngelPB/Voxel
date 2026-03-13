#version 330 core

uniform sampler2D screenTexture;
in vec2 uv;
out vec4 outColor;

void main()
{
    outColor = texture(screenTexture, uv);
    //outColor = vec4(1.0, 0.0, 0.0, 1.0);
}