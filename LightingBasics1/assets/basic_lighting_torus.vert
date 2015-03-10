#version 150

uniform mat4 ciModelViewProjection;
uniform mat4 ciModelMatrix;
in vec4 ciPosition;
in vec3 ciNormal;
in vec3 iPosition;
in vec4 iColor;

out vec4 Color;
out vec3 ObjectNormal;
out vec4 WorldPosition;

void main()
{
	Color = iColor;
	ObjectNormal = ciNormal;
	WorldPosition = ciModelMatrix*ciPosition;
	gl_Position = ciModelViewProjection * (4.0*ciPosition + vec4(iPosition,0));
}