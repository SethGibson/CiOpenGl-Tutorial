uniform sampler2D u_SamplerRGB;

in vec2 UV;
out vec4 o_Color;

void main()
{
	//Nothing special to see here
	o_Color = texture2D(u_SamplerRGB, UV);
}