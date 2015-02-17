#version 150

in vec4 Color;
in vec2 TexCoord;
out vec4 oColor;
uniform sampler2D texRgb;

void main()
{
	oColor = texture2D(texRgb, TexCoord);
	oColor *= Color;
}