#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    // note that we read the multiplication from right to left
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0f);
}
