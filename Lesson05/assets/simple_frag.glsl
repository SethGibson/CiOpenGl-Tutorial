#version 150

uniform sampler2D texRGB;
in vec4 Color;
in vec2 TexCoord;
out vec4 oColor;


void main()
{
	oColor = texture2D(texRGB, TexCoord);
	oColor *= Color;
}