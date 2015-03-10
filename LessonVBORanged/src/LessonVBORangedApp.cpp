#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/MayaCamUI.h"
#include "cinder/Rand.h"
using namespace ci;
using namespace ci::app;
using namespace std;

static int S_BUFFER_DIM = 512;

class LessonVBORangedApp : public AppNative
{
public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void mouseDrag(MouseEvent event) override;
	void update() override;
	void draw() override;

	struct RPoint
	{
		vec3 PPosition;
		Color PColor;

		RPoint(vec3 pPos, Color pCol) : PPosition(pPos), PColor(pCol){}
	};

private:
	gl::VboRef mBufferObj;
	gl::VboMeshRef mMeshObj;
	gl::BatchRef mDrawObj;
	geom::BufferLayout mAttribsObj;
	gl::GlslProgRef mShaderObj;

	vector<vec3> mPositions;
	CameraPersp mCamera;
	MayaCamUI mMaya;
};

void LessonVBORangedApp::setup()
{
	getWindow()->setSize(1280, 720);
	try
	{
		mShaderObj = gl::GlslProg::create(loadAsset("vbo_ranged_vert.glsl"), loadAsset("vbo_ranged_frag.glsl"));
	}
	catch (const gl::GlslProgExc &e)
	{
		console() << "Error loading shaders:" << endl;
		console() << e.what() << endl;
	}
	catch (...)
	{

	}
	//setup positions
	for (int py = 0; py < S_BUFFER_DIM; ++py)
	{
		for (int px = 0; px < S_BUFFER_DIM; ++px)
		{
			mPositions.push_back(vec3(lmap<float>(px, 0, S_BUFFER_DIM, -1.6f, 1.6f),
										lmap<float>(py, 0, S_BUFFER_DIM, -0.9f, 0.9f),
										0.0f));
		}
	}

	mBufferObj = gl::Vbo::create(GL_ARRAY_BUFFER, mPositions, GL_DYNAMIC_DRAW);
	mAttribsObj.append(geom::Attrib::POSITION, 3, 0, 0, 0);
	mMeshObj = gl::VboMesh::create(mPositions.size(), GL_POINTS, { { mAttribsObj, mBufferObj } });
	mDrawObj = gl::Batch::create(mMeshObj, mShaderObj);

	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1, 100.0f);
	mCamera.lookAt(vec3(0, 0, 3), vec3(0), vec3(0, 1, 0));
	mCamera.setCenterOfInterestPoint(vec3(0));
	mMaya.setCurrentCam(mCamera);
}

void LessonVBORangedApp::mouseDown( MouseEvent event )
{
	mMaya.mouseDown(event.getPos());
}

void LessonVBORangedApp::mouseDrag(MouseEvent event)
{
	mMaya.mouseDrag(event.getPos(), event.isLeftDown(), false, event.isRightDown());
}

void LessonVBORangedApp::update()
{
	//int cDim = randI
	//mBufferObj->mapBufferRange(0,;
}

void LessonVBORangedApp::draw()
{
	gl::clear( Color( 0.1f, 0.15f, 0.25f ) ); 
	gl::setMatrices(mMaya.getCamera());
	mDrawObj->draw();
}

CINDER_APP_NATIVE( LessonVBORangedApp, RendererGl )
