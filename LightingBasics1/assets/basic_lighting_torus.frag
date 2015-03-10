#version 150

uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform float AmbientScale;
in vec4 Color;
in vec3 ObjectNormal;
in vec4 WorldPosition;
out vec4 oColor;

void main()
{
	vec3 cLightDir = normalize(LightPosition - vec3(WorldPosition.xyz));
	vec3 cNormal = normalize(ObjectNormal);

	float cDiffTerm = max(dot(cLightDir, cNormal), 0.0);
	vec3 cDiffContrib = LightColor * cDiffTerm;
	vec3 cAmbientContrib = LightColor * AmbientScale;
	vec3 cLightContrib = cDiffContrib+cAmbientContrib;

	oColor = Color * vec4(cLightContrib,1);
}