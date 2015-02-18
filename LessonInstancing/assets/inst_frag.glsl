#version 150

uniform sampler2D texRgb;
in vec2 TexCoord;
in vec4 Color;

out vec4 oColor;

void main()
{
	oColor = texture2D(texRgb, TexCoord);
	oColor*=Color;
}