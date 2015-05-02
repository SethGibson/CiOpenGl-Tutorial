#version 150

uniform mat4 ciModelViewProjection;

in vec4 ciPosition;		//source mesh vertex position
in vec2 ciTexCoord0;	//source mesh texture coordinate

in vec3 iPosition;		//per-instance mesh position ("mesh center")
in vec4 iColor;			//per-instance mesh color
in float iSize;			//per-instance mesh size

out vec2 TexCoord;
out vec4 Color;

void main()
{
	Color = iColor;
	TexCoord = ciTexCoord0;

	//First we scale the incoming vertex position by size
	vec4 cScaled = ciPosition * vec4(iSize,iSize,iSize,1.0);

	//Next, we offset the scaled position by the per-instance position
	vec4 cTranslated = cScaled + vec4(iPosition,1.0);

	//Finally, we transform the scaled and translated position into clip space
	gl_Position = ciModelViewProjection * cTranslated;
}