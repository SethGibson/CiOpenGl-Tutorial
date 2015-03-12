#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/GeomIo.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonIndexedVBOApp : public App
{
public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void update() override;
	void draw() override;

	gl::VboRef mPositionData, mIndexData;
	gl::VboMeshRef mVboMesh;
	geom::BufferLayout mPositionLayout, mIndexLayout;
	gl::BatchRef mBatch;
	gl::GlslProgRef mGlsl;

	CameraPersp mCamera;
};

void LessonIndexedVBOApp::setup()
{
	try
	{
		mGlsl = gl::GlslProg::create(loadAsset("inst_simple_vert.glsl"), loadAsset("inst_simple_frag.glsl"));
	}
	catch (const gl::GlslProgExc &e)
	{
		console() << "Error loading shader:" << endl;
		console() << e.what() << endl;
		quit();
	}
	vector<vec3> cVerts =
	{
		vec3(-1.0, -1.0, 0.0), vec3(-1.0, 1.0, 0.0), vec3(1.0, 1.0, 0.0), vec3(1.0, -1.0, 0.0)
	};

	vector<unsigned short> cIndices =
	{
		0, 2, 1, 0, 3, 2
	};

	mPositionData = gl::Vbo::create(GL_ARRAY_BUFFER, cVerts, GL_STATIC_DRAW);
	mPositionLayout.append(geom::Attrib::POSITION, 3, 0, 0, 0);

	mIndexData = gl::Vbo::create(GL_ELEMENT_ARRAY_BUFFER, cIndices, GL_STATIC_DRAW);
	mVboMesh = gl::VboMesh::create(4, GL_TRIANGLES, { { mPositionLayout, mPositionData } }, cIndices.size(), GL_UNSIGNED_SHORT, mIndexData);

	mBatch = gl::Batch::create(mVboMesh, mGlsl);

	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 100.0f);
	mCamera.lookAt(vec3(3, 3, 3), vec3(0), vec3(0, 1, 0));
}

void LessonIndexedVBOApp::mouseDown(MouseEvent event)
{

}

void LessonIndexedVBOApp::update()
{

}

void LessonIndexedVBOApp::draw()
{
	gl::clear(Color(0.1f, 0.15f, 0.25f));
	gl::setMatrices(mCamera);
	mBatch->draw();
}

CINDER_APP(LessonIndexedVBOApp, RendererGl)
