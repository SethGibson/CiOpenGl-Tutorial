#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonLightingBasics2App : public App
{
public:
	void setup();
	void update();
	void draw();

	struct ISphere
	{
		vec3 IPosition;
		vec4 IColor;
		ISphere(vec3 pPos, vec4 pCol) :IPosition(pPos), IColor(pCol){}
	};
private:
	gl::VboRef				mInstanceData;
	geom::BufferLayout		mInstanceAttribs;
	gl::VboMeshRef			mTorusMesh;
	gl::BatchRef			mTorusBatch;
	gl::GlslProgRef			mTorusShader;

	vec3					mLightPos;
	Color					mLightColor;
	float					mAmbientScale, mSpecScale, mSpecPow;
	gl::VboMeshRef			mLightMesh;
	gl::BatchRef			mLightBatch;
	gl::GlslProgRef			mLightShader;

	gl::VboMeshRef			mPlaneMesh;
	gl::BatchRef			mPlaneBatch;
	gl::GlslProgRef			mPlaneShader;

	CameraPersp				mCamera;
	CameraUi				mCamUI;

	params::InterfaceGlRef	mGUI;
};

void LessonLightingBasics2App::setup()
{
	getWindow()->setSize(1280, 720);
	mLightColor = Color(1, 1, 0);
	mLightPos = vec3(0, 0.75, 0);
	mAmbientScale = 1.0f;
	mSpecScale = 1.0f;
	mSpecPow = 32.f;

	try
	{
		mTorusShader = gl::GlslProg::create(loadAsset("basic_lighting_torus.vert"), loadAsset("basic_lighting_torus.frag"));
		mLightShader = gl::GlslProg::create(loadAsset("basic_lighting_light.vert"), loadAsset("basic_lighting_light.frag"));
		mPlaneShader = gl::GlslProg::create(loadAsset("basic_lighting_plane.vert"), loadAsset("basic_lighting_plane.frag"));
	}
	catch (const gl::GlslProgExc &e)
	{
		console() << e.what() << endl;
	}

	vector<ISphere> cPositions =
	{
		ISphere(vec3(-1.25, 0.75, -1.25), vec4(0.5, 0.25, 0, 1)),
		ISphere(vec3(1.25, 0.75, -1.25), vec4(0.25, 0.25, 0.1, 1)),
		ISphere(vec3(-1.25, 0.75, 1.25), vec4(0.1, 0.25, 0.25, 1)),
		ISphere(vec3(1.25, 0.75, 1.25), vec4(0.0, 0.25, 0.5, 1))
	};

	mTorusMesh = gl::VboMesh::create(geom::Sphere().radius(0.15f));
	mInstanceData = gl::Vbo::create(GL_ARRAY_BUFFER, cPositions, GL_STATIC_DRAW);
	mInstanceAttribs.append(geom::CUSTOM_0, 3, sizeof(ISphere), offsetof(ISphere, IPosition), 1);
	mInstanceAttribs.append(geom::CUSTOM_1, 4, sizeof(ISphere), offsetof(ISphere, IColor), 1);
	mTorusMesh->appendVbo(mInstanceAttribs, mInstanceData);
	mTorusBatch = gl::Batch::create(mTorusMesh, mTorusShader, { { geom::CUSTOM_0, "iPosition" }, { geom::CUSTOM_1, "iColor" } });
	mTorusBatch->getGlslProg()->uniform("LightPosition", mLightPos);
	mTorusBatch->getGlslProg()->uniform("LightColor", mLightColor);
	mTorusBatch->getGlslProg()->uniform("AmbientScale", mAmbientScale);
	mTorusBatch->getGlslProg()->uniform("SpecularScale", mSpecScale);
	mTorusBatch->getGlslProg()->uniform("SpecularPower", mSpecPow);

	mLightMesh = gl::VboMesh::create(geom::Sphere().subdivisions(16).center(mLightPos).radius(0.01f));
	mLightBatch = gl::Batch::create(mLightMesh, mLightShader);
	mLightBatch->getGlslProg()->uniform("LightColor", mLightColor);


	mPlaneMesh = gl::VboMesh::create(geom::Plane());
	mPlaneBatch = gl::Batch::create(mPlaneMesh, mPlaneShader);

	vec3 cEyePos(0, 0.65f, -2.25f);
	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 100.0f);
	mCamera.lookAt(cEyePos, vec3(0), vec3(0, 1, 0));
	mCamera.setPivotDistance(length(cEyePos));
	mCamUI = CameraUi(&mCamera, getWindow());

	mGUI = params::InterfaceGl::create("Params", vec2(200, 200));
	mGUI->addParam("Light Color", &mLightColor);
	mGUI->addParam("Ambient Strength", &mAmbientScale);
	mGUI->addParam("Specular Strength", &mSpecScale);
	mGUI->addParam("Specular Power", &mSpecPow);

	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void LessonLightingBasics2App::update()
{
}

void LessonLightingBasics2App::draw()
{
	// clear out the window with black
	gl::clear(Color(0, 0, 0));
	gl::setMatrices(mCamera);

	mPlaneBatch->draw();

	gl::pushMatrices();
	mLightPos.x = math<float>::sin(getElapsedSeconds());
	mLightPos.z = math<float>::cos(getElapsedSeconds());
	gl::translate(mLightPos);
	mLightBatch->getGlslProg()->uniform("LightColor", mLightColor);
	mLightBatch->draw();
	gl::popMatrices();

	mTorusBatch->getGlslProg()->uniform("ViewDirection", mCamera.getViewDirection());
	mTorusBatch->getGlslProg()->uniform("LightPosition", mLightPos);
	mTorusBatch->getGlslProg()->uniform("LightColor", mLightColor);
	mTorusBatch->getGlslProg()->uniform("AmbientScale", mAmbientScale);
	mTorusBatch->getGlslProg()->uniform("SpecularScale", mSpecScale);
	mTorusBatch->getGlslProg()->uniform("SpecularPower", mSpecPow);
	mTorusBatch->drawInstanced(4);

	gl::setMatricesWindow(getWindowSize());
	mGUI->draw();
}

CINDER_APP(LessonLightingBasics2App, RendererGl)
