#version 150

uniform vec3 ViewDirection;
uniform vec3 LightColor;
uniform vec3 LightPosition;

uniform float SpecularScale;
uniform float SpecularPower;
uniform float AmbientScale;

in vec4 Color;
in vec3 ObjectNormal;
in vec4 WorldPosition;

out vec4 oColor;

void main()
{
	vec3 cNormal = normalize(ObjectNormal);
	vec3 cLightDir = normalize(LightPosition - WorldPosition.xyz);
	vec3 cEyeDir = normalize(ViewDirection);
	vec3 cReflectDir = reflect(cLightDir, cNormal);

	float cDiffTerm = max(dot(cLightDir, cNormal), 0.0);
	float cSpecTerm = pow(max(dot(cEyeDir, cReflectDir), 0), SpecularPower);

	vec3 cDiffContrib = LightColor * cDiffTerm;
	vec3 cSpecContrib = SpecularScale * cSpecTerm * LightColor;
	vec3 cAmbientContrib = LightColor * AmbientScale;
	vec3 cLightContrib = cDiffContrib+cAmbientContrib+cSpecContrib;

	oColor = Color * vec4(cLightContrib,1);
}