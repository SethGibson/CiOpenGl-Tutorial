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
	
	ObjectNormal = mat3(transpose(inverse(ciModelMatrix)))*ciNormal;

	vec4 cInstPos = ciPosition + vec4(iPosition,1.0);
	WorldPosition = ciModelMatrix*cInstPos;
	gl_Position = ciModelViewProjection * cInstPos;
}