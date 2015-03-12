/* Cinder OpenGL-Tutorial - Cinder GL tutorials based on www.opengl-tutorial.org

Lesson 04a: Texturing
Original Tutorial:
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/

Let's apply a texture to a primitive.  For simplicity's sake, we'll use a plane instead of a cube, and
we'll use multiple VBOs.  Next tutorial we'll look at using structs to pass multiple attribute datasets
to the VBO.
*/

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson04App : public App {
public:
	void	setup() override;
	void	update() override;
	void	draw() override;


	gl::GlslProgRef		mGlsl;
	gl::VboRef			mPositionData, mColorData, mUVData;
	geom::BufferLayout	mPositionLayout, mColorLayout, mUVLayout;
	gl::VboMeshRef		mMesh;
	gl::BatchRef		mBatch;
	gl::Texture2dRef	mTexture;
	CameraPersp			mCamera;
};

void Lesson04App::setup()
{
	getWindow()->setSize(1024, 768);

	mTexture = gl::Texture2d::create(loadImage(loadAsset("texture.png")));
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
	mCamera.lookAt(vec3(0, -3, 3), vec3(0), vec3(0, 1, 0));

	vector<vec3> cVertices =
	{
		vec3(1.0f, 1.0f, 0.0f), vec3(-1.0f, 1.0f, 0.0f),	vec3(-1.0f, -1.0f, 0.0f),
		vec3(1.0f, 1.0f, 0.0f), vec3(-1.0f, -1.0f, 0.0f),	vec3(1.0f, -1.0f, 0.0f),
	};

	vector<vec4> cColors =
	{
		vec4(0.583f, 0.771f, 0.014f, 1.0f), vec4(0.609f, 0.115f, 0.436f, 1.0f), vec4(0.327f, 0.483f, 0.844f, 1.0f),
		vec4(0.822f, 0.569f, 0.201f, 1.0f), vec4(0.435f, 0.602f, 0.223f, 1.0f), vec4(0.310f, 0.747f, 0.185f, 1.0f),
	};

	vector<vec2> cUVs =
	{
		vec2(1.0,1.0), vec2(0.0,1.0), vec2(0.0,0.0),
		vec2(1.0,1.0), vec2(0.0,0.0), vec2(1.0,0.0)
	};

	mPositionData = gl::Vbo::create(GL_ARRAY_BUFFER, cVertices, GL_STATIC_DRAW);
	mPositionLayout.append(geom::Attrib::POSITION, geom::DataType::FLOAT, 3, 0, 0);

	mColorData = gl::Vbo::create(GL_ARRAY_BUFFER, cColors, GL_STATIC_DRAW);
	mColorLayout.append(geom::Attrib::COLOR, geom::DataType::FLOAT, 4, 0, 0);

	mUVData = gl::Vbo::create(GL_ARRAY_BUFFER, cUVs, GL_STATIC_DRAW);
	mUVLayout.append(geom::Attrib::TEX_COORD_0, geom::DataType::FLOAT, 2, 0, 0);

	mMesh = gl::VboMesh::create(6, GL_TRIANGLES, { { mPositionLayout, mPositionData }, { mColorLayout, mColorData }, {mUVLayout, mUVData} });
	mBatch = gl::Batch::create(mMesh, mGlsl);
}

void Lesson04App::update()
{
}

void Lesson04App::draw()
{
	gl::enableDepthRead();
	gl::enableDepthWrite();

	gl::clear(Color(0.1f, 0.15f, 0.25f));
	gl::setMatrices(mCamera);
	
	gl::ScopedTextureBind cTexture(mTexture);
	mBatch->draw();
}

CINDER_APP( Lesson04App, RendererGl )
