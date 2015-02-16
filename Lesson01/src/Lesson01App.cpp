#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson01App : public AppNative {
public:
	void	setup() override;
	void	resize() override;
	void	update() override;
	void	draw() override;

	void setupVboMesh();
	void drawVboMesh();

	CameraPersp			mCam;
	gl::BatchRef		mBatch;
	gl::GlslProgRef		mGlsl;
	mat4				mCubeRotation;

	//setupVboMesh
	gl::VboRef mShapeVbo;
	gl::VboMeshRef mShapeMesh;
	geom::BufferLayout mShapeLayout;

};

void Lesson01App::setup()
{
	getWindow()->setSize(500, 500);

	float cWidth = (float)getWindowWidth();
	float cHeight = (float)getWindowHeight();
	vector<vec3> cVertices = { vec3(0.0, cWidth, 0.0),
		vec3(cWidth, cHeight, 0.0),
		vec3(cWidth/2, 0.0, 0.0)

	};

	mGlsl = gl::GlslProg::create(loadAsset("simple_vert.glsl"), loadAsset("simple_frag.glsl"));
	mShapeVbo = gl::Vbo::create(GL_ARRAY_BUFFER, cVertices, GL_STATIC_DRAW);
	mShapeLayout.append(geom::Attrib::POSITION, 3, sizeof(vec3), 0);
	mShapeMesh = gl::VboMesh::create(3, GL_TRIANGLES, { { mShapeLayout, mShapeVbo } });
	mBatch = gl::Batch::create(mShapeMesh, mGlsl);

}


void Lesson01App::resize()
{
	mCam.setPerspective(60, getWindowAspectRatio(), 1, 1000);
	gl::setMatrices(mCam);
}

void Lesson01App::update()
{
}

void Lesson01App::draw()
{
	gl::clear();
	gl::setMatricesWindowPersp(getWindowSize());
	gl::enableDepthWrite();
	gl::enableDepthRead();
	mBatch->draw();
}

CINDER_APP_NATIVE( Lesson01App, RendererGl )