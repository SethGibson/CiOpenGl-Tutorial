/* Cinder OpenGL-Tutorial - Cinder GL tutorials based on www.opengl-tutorial.org

Lesson 03: Colored cube
Original Tutorial:
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/

In this tutorial, we'll take a look at cinder's geom pipeline and practice setting up
more attributes.
*/

#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/GeomIo.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson02App : public AppNative {
public:
	void	setup() override;
	void	update() override;
	void	draw() override;

	gl::GlslProgRef		mGlsl;
	geom::Cube			mCube;
	gl::BatchRef		mBatch;

	CameraPersp			mCamera;
};

void Lesson02App::setup()
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

	// Now the view matrix.  Once again, note the mapping:
	mCamera.lookAt(vec3(4, 3, 3), vec3(0), vec3(0, 1, 0));

	//	Since we're in 3d space now, we'll change our vertex coords to properly reflect
	//	our new camera based viewport.  Everything else pretty much stays the same.
	vector<vec3> cVertices = { vec3(-1.0, -1.0, 0.0),
		vec3(1.0, -1.0, 0.0),
		vec3(0.0, 1.0, 0.0) };

	mShapeVbo = gl::Vbo::create(GL_ARRAY_BUFFER, cVertices, GL_STATIC_DRAW);
	mShapeLayout.append(geom::Attrib::POSITION, geom::DataType::FLOAT, 3, sizeof(vec3), 0);
	mShapeMesh = gl::VboMesh::create(3, GL_TRIANGLES, { { mShapeLayout, mShapeVbo } });
	mBatch = gl::Batch::create(mShapeMesh, mGlsl);
}

void Lesson02App::update()
{
}

void Lesson02App::draw()
{
	gl::clear(Color(0, 0, 0.15f));

	//	Now we set our modelviewprojection matrix, based on the camera we set up earlier.
	//	Everything will be drawin relative to the camera until we specify new matrices.
	gl::setMatrices(mCamera);
	mBatch->draw();
}

CINDER_APP_NATIVE( Lesson03App, RendererGl )
