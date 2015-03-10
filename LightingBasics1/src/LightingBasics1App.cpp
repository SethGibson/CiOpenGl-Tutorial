#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/Camera.h"
#include "cinder/MayaCamUI.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LightingBasics1App : public AppNative
{
public:
	void setup();
	void mouseDown( MouseEvent event );	
	void mouseDrag(MouseEvent event);
	void update();
	void draw();

private:
	gl::VboRef			mInstanceData;
	geom::BufferLayout	mInstanceAttribs;
	gl::VboMeshRef		mTorusMesh;
	gl::BatchRef		mTorusBatch;
	gl::GlslProgRef		mTorusShader;

	gl::VboMeshRef		mLightMesh;
	gl::BatchRef		mLightBatch;
	gl::GlslProgRef		mLightShader;

	gl::VboMeshRef		mPlaneMesh;
	gl::BatchRef		mPlaneBatch;
	gl::GlslProgRef		mPlaneShader;

	CameraPersp			mCamera;
	MayaCamUI			mMayaUI;
};

void LightingBasics1App::setup()
{
	getWindow()->setSize(1280, 720);

	try
	{
		//mTorusShader = gl::GlslProg::create(loadAsset("basic_lighting_torus.vert"), loadAsset("basic_lighting_torus.frag"));
		mLightShader = gl::GlslProg::create(loadAsset("basic_lighting_light.vert"), loadAsset("basic_lighting_light.frag"));
		mPlaneShader = gl::GlslProg::create(loadAsset("basic_lighting_plane.vert"), loadAsset("basic_lighting_plane.frag"));
	}
	catch (const gl::GlslProgExc &e)
	{
		console() << e.what() << endl;
	}
	/*
	vector<vec3> cPositions = { vec3(-1, 1, -1), vec3(1, 1, -1), vec3(-1, 1, 1), vec3(1, 1, 1) };
	mTorusMesh = gl::VboMesh::create(geom::Torus());
	mInstanceData = gl::Vbo::create(GL_ARRAY_BUFFER, cPositions, GL_STATIC_DRAW);
	mInstanceAttribs.append(geom::CUSTOM_0, 3, 0, 0, 1);
	mTorusMesh->appendVbo(mInstanceAttribs, mInstanceData);
	mTorusBatch = gl::Batch::create(mTorusMesh, mTorusShader, { {geom::CUSTOM_0, "iPosition"} });
	*/
	mLightMesh = gl::VboMesh::create(geom::Sphere().subdivisions(16).center(vec3(2,1,2)).radius(0.1f));
	mLightBatch = gl::Batch::create(mLightMesh, mLightShader);

	mPlaneMesh = gl::VboMesh::create(geom::Plane().size(vec2(3)));
	mPlaneBatch = gl::Batch::create(mPlaneMesh, mPlaneShader);

	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 100.0f);
	mCamera.lookAt(vec3(0, 0.65f, -2.25f), vec3(0), vec3(0, 1, 0));
	mCamera.setCenterOfInterestPoint(vec3(0));
	mMayaUI.setCurrentCam(mCamera);

	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void LightingBasics1App::mouseDown( MouseEvent event )
{
	mMayaUI.mouseDown(event.getPos());
}

void LightingBasics1App::mouseDrag(MouseEvent event)
{
	mMayaUI.mouseDrag(event.getPos(), event.isLeftDown(), false, event.isRightDown());
}

void LightingBasics1App::update()
{
}

void LightingBasics1App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::setMatrices(mMayaUI.getCamera());
	
	mPlaneBatch->draw();
	mLightBatch->draw();
	//mTorusBatch->drawInstanced(4);
}

CINDER_APP_NATIVE( LightingBasics1App, RendererGl )
