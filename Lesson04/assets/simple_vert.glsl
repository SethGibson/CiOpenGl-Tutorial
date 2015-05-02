#version 150

uniform mat4	ciModelViewProjection;

in vec4		ciPosition;
in vec2		ciTexCoord0;
in vec4		ciColor;

out highp vec2	TexCoord;
out lowp vec4	Color;

void main( void )
{
	gl_Position	= ciModelViewProjection * ciPosition;
	Color 		= ciColor;
	TexCoord	= ciTexCoord0;
}