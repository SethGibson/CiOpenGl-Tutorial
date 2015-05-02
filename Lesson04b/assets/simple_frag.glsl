#version 150

uniform sampler2D texRgb;

in vec4 Color;
in vec2 TexCoord;

out vec4 oColor;


void main()
{
	oColor = texture2D(texRgb, TexCoord);
	oColor *= Color;
}