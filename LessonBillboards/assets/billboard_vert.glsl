uniform mat4 ciModelViewProjection;			//model-view-projection matrix for final transform
uniform vec3 u_CameraUp;					//camera up vector (from the app)
uniform vec3 u_CameraRight;					//camera right vector (from the app)

in vec4 ciPosition;							//per-instance mesh vertex position
in vec2 ciTexCoord0;	

in vec3 i_Position;							//per-instance mesh position

out vec2 UV;

void main()
{

	UV = ciTexCoord0;

	//here we short cut a matrix transformation to get the billboarding effect
	//matrix * vector is basically column * vector_component, so this should
	//make sense:
	vec3 mBillboard = i_Position + u_CameraRight*ciPosition.x*0.75 + u_CameraUp*ciPosition.y*0.75;

	//and now we transform the billboarded position into clip-space
	gl_Position = ciModelViewProjection * vec4(mBillboard, 1.0);

}