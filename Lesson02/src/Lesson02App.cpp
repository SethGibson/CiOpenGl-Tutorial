/* Cinder OpenGL-Tutorial - Cinder GL tutorials based on www.opengl-tutorial.org

Lesson 02: Camera
Original Tutorial:
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

We're deviating a bit from the original tutorial here as we won't implement all
the matrix math ourselves, instead we'll learn how to work with Cinder's CameraPersp.
I recommend reading the original tutorial as it'll give you a good understanding of what
CameraPersp is probably doing under the hood.
*/

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson02App : public App {
public:
	void	setup() override;
	void	update() override;
	void	draw() override;

	gl::GlslProgRef		mGlsl;
	gl::VboRef			mShapeVbo;
	geom::BufferLayout	mShapeLayout;
	gl::VboMeshRef		mShapeMesh;
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

	//	Let's set up our camera now.  All sorts of matrix magic happens here, and you'll notice that
	//	the commands and parameters map 1-to-1.
	//	So, perspective matrix first.  Note how CameraPersp::setPerspective() maps to
	//	glm::perspective():
	//glm::mat4 perspective(float fovy, float aspect, float zNear, float zFar);
	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 100.0f);

	// Now the view matrix.  Once again, note the mapping:
	// glm::mat4 glm::lookAt(glm::vec3 const & eye,	glm::vec3 const & center, glm::vec3 const & up);
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
	//	Everything will be drawn relative to the camera until we specify new matrices.
	gl::setMatrices(mCamera);
	mBatch->draw();
}
CINDER_APP( Lesson02App, RendererGl )
