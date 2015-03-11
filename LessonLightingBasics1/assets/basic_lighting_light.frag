#version 150

uniform vec3 LightColor;
out vec4 oColor;

void main()
{
	oColor = vec4(LightColor,1);
}