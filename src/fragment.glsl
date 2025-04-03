#version 430 core

out vec4 FragColor;

uniform vec4 u_Color = vec4(1.0);

void main()
{
    vec4 color = u_Color;
    FragColor = color;
}
