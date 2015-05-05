#version 150
uniform mat4 ciViewMatrix;
uniform mat4 ciProjectionMatrix;
uniform vec3 u_CameraRight;
uniform vec3 u_CameraUp;

in vec4 ciPosition;

in mat4 iModelMatrix;
in vec3 iPosition;
in vec4 iColor;
in float iSize;

out vec4 Color;

void main()
{
	//If this all looks familiar, it should! We're not doing too much different
	//from the previous instancing sample, the only major change is that
	//instead of using the default model-view-projection matrix,
	//we're constructing our own from per-instance attribute data

	//Transform the point into "billboard" space;
	vec3 cPosition = iPosition + u_CameraRight*ciPosition.x*iSize+u_CameraUp*ciPosition.y*iSize;

	//Transform the position into clip space, remember matrix concatenation is RIGHT TO LEFT!
	gl_Position = ciProjectionMatrix * ciViewMatrix * iModelMatrix * vec4(cPosition,1.0);
	Color = iColor;
}