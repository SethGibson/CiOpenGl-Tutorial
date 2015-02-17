/* Cinder OpenGL-Tutorial - Cinder GL tutorials based on www.opengl-tutorial.org

Lesson 03: Colored cube
Original Tutorial:
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/

In this tutorial, we'll draw an actual 3d primitive and practice setting up more attributes.
*/

#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson03App : public AppNative {
public:
	void	setup() override;
	void	update() override;
	void	draw() override;


	gl::GlslProgRef		mGlsl;
	gl::VboRef			mPositionData, mColorData;
	geom::BufferLayout	mPositionLayout, mColorLayout;
	gl::VboMeshRef		mCubeMesh;
	gl::BatchRef		mBatch;

	CameraPersp			mCamera;
};

void Lesson03App::setup()
{
	getWindow()->setSize(1024, 768);
	try
	{
		mGlsl = gl::GlslProg::create(loadAsset("simple_vert.glsl"), loadAsset("simple_frag.glsl"));
	}
	catch (const gl::GlslProgExc &e)
	{
		console() << "Error loading shaders:" << endl;
		console() << e.what() << endl;
		quit();
	}

	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 100.0f);
	mCamera.lookAt(vec3(3, 3, 3), vec3(0), vec3(0, 1, 0));

	// Since we're creating a cube, that means many more verts!
	vector<vec3> cVertices =
	{
		vec3(-1.0f, -1.0f, -1.0f),	vec3(-1.0f, -1.0f, 1.0f),	vec3(-1.0f, 1.0f, 1.0f),
		vec3(-1.0f, -1.0f, -1.0f),	vec3(-1.0f, 1.0f, 1.0f),	vec3(-1.0f, 1.0f, -1.0f),
		vec3(1.0f, 1.0f, 1.0f),		vec3(1.0f, 1.0f, -1.0f),	vec3(-1.0f, 1.0f, -1.0f),
		vec3(1.0f, 1.0f, 1.0f),		vec3(-1.0f, 1.0f, -1.0f),	vec3(-1.0f, 1.0f, 1.0f),
		vec3(1.0f, -1.0f, -1.0f),	vec3(1.0f, -1.0f, 1.0f),	vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, -1.0f, -1.0f),	vec3(1.0f, 1.0f, 1.0f),		vec3(1.0f, 1.0f, -1.0f),
		vec3(1.0f, -1.0f, 1.0f),	vec3(-1.0f, -1.0f, -1.0f),	vec3(1.0f, -1.0f, -1.0f),
		vec3(1.0f, -1.0f, 1.0f),	vec3(-1.0f, -1.0f, 1.0f),	vec3(-1.0f, -1.0f, -1.0f),
		vec3(1.0f, 1.0f, -1.0f),	vec3(-1.0f, -1.0f, -1.0f),	vec3(-1.0f, 1.0f, -1.0f),
		vec3(1.0f, 1.0f, -1.0f),	vec3(1.0f, -1.0f, -1.0f),	vec3(-1.0f, -1.0f, -1.0f),
		vec3(-1.0f, 1.0f, 1.0f),	vec3(-1.0f, -1.0f, 1.0f),	vec3(1.0f, -1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),		vec3(-1.0f, 1.0f, 1.0f),	vec3(1.0f, -1.0f, 1.0f)
	};

	vector<vec4> cColors = 
	{
		vec4(0.583f, 0.771f, 0.014f, 1.0f), vec4(0.609f, 0.115f, 0.436f, 1.0f), vec4(0.327f, 0.483f, 0.844f, 1.0f),
		vec4(0.822f, 0.569f, 0.201f, 1.0f), vec4(0.435f, 0.602f, 0.223f, 1.0f), vec4(0.310f, 0.747f, 0.185f, 1.0f),
		vec4(0.597f, 0.770f, 0.761f, 1.0f), vec4(0.559f, 0.436f, 0.730f, 1.0f), vec4(0.359f, 0.583f, 0.152f, 1.0f),
		vec4(0.483f, 0.596f, 0.789f, 1.0f), vec4(0.559f, 0.861f, 0.639f, 1.0f), vec4(0.195f, 0.548f, 0.859f, 1.0f),
		vec4(0.014f, 0.184f, 0.576f, 1.0f), vec4(0.771f, 0.328f, 0.970f, 1.0f), vec4(0.406f, 0.615f, 0.116f, 1.0f),
		vec4(0.676f, 0.977f, 0.133f, 1.0f), vec4(0.971f, 0.572f, 0.833f, 1.0f), vec4(0.140f, 0.616f, 0.489f, 1.0f),
		vec4(0.997f, 0.513f, 0.064f, 1.0f), vec4(0.945f, 0.719f, 0.592f, 1.0f), vec4(0.543f, 0.021f, 0.978f, 1.0f),
		vec4(0.279f, 0.317f, 0.505f, 1.0f), vec4(0.167f, 0.620f, 0.077f, 1.0f), vec4(0.347f, 0.857f, 0.137f, 1.0f),
		vec4(0.055f, 0.953f, 0.042f, 1.0f), vec4(0.714f, 0.505f, 0.345f, 1.0f), vec4(0.783f, 0.290f, 0.734f, 1.0f),
		vec4(0.722f, 0.645f, 0.174f, 1.0f), vec4(0.302f, 0.455f, 0.848f, 1.0f), vec4(0.225f, 0.587f, 0.040f, 1.0f),
		vec4(0.517f, 0.713f, 0.338f, 1.0f), vec4(0.053f, 0.959f, 0.120f, 1.0f), vec4(0.393f, 0.621f, 0.362f, 1.0f),
		vec4(0.673f, 0.211f, 0.457f, 1.0f), vec4(0.820f, 0.883f, 0.371f, 1.0f), vec4(0.982f, 0.099f, 0.879, 1.0f)
	};

	mPositionData = gl::Vbo::create(GL_ARRAY_BUFFER, cVertices, GL_STATIC_DRAW);
	mPositionLayout.append(geom::Attrib::POSITION, geom::DataType::FLOAT, 3, sizeof(vec3), 0);

	mColorData = gl::Vbo::create(GL_ARRAY_BUFFER, cColors, GL_STATIC_DRAW);
	mColorLayout.append(geom::Attrib::COLOR, geom::DataType::FLOAT, 4, sizeof(vec4), 0);

	mCubeMesh = gl::VboMesh::create(36, GL_TRIANGLES, { { mPositionLayout, mPositionData }, { mColorLayout, mColorData } });
	mBatch = gl::Batch::create(mCubeMesh, mGlsl);
}

void Lesson03App::update()
{
}

void Lesson03App::draw()
{
	gl::enableDepthRead();
	gl::enableDepthWrite();

	gl::clear(Color(0, 0, 0.15f));
	gl::setMatrices(mCamera);
	mBatch->draw();
}

CINDER_APP_NATIVE( Lesson03App, RendererGl )
