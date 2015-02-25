#version 150

uniform mat4	ciModelViewProjection;
uniform float	ciElapsedSeconds;
in vec4			ciPosition;
in vec4			ciColor;

out vec4		Color;

void main( void )
{
	vec4 cPos = ciPosition;
	cPos.z = cos((ciPosition.x+ciPosition.y)+ciElapsedSeconds);
	gl_Position = ciModelViewProjection * cPos;
	float cR = sin(cPos.x);
	float cG = cos(cPos.y);
	float cB = (sin(cPos.z) + cos(cPos.z))*0.5;
	cR = (cR + 1.0)*0.5;
	cG = (cG + 1.0)*0.5;
	cB = (cB + 1.0)*0.5;
	Color = vec4(cR,cG,cB,1.0);
}