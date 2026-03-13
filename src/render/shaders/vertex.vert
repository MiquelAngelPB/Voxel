#version 330 core
layout(location = 0) in vec2 inPos;
out vec2 uv;

void main()
{
   uv = inPos * 0.5 + 0.5;
   gl_Position = vec4(inPos, 0.0, 1.0);
}