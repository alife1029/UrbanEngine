#version 330 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec4 a_Color;

uniform mat4 u_ViewProj;

out vec4 v_Color;

void main()
{
	v_Color = a_Color;
	gl_Position = u_ViewProj * vec4(a_Position, 0.0, 1.0);
}