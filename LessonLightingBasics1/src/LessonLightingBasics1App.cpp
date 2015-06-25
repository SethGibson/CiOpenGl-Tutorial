/*
Cinder OpenGL-Tutorial - Cinder GL tutorials based on www.opengl-tutorial.org

Basic Lighting: A simple ambient+diffuse+specular per-pixel lighting implementation
We'll also look at how to use Cinder's built in params window to control our shader parameters

Reference:
http://learnopengl.com/#!Lighting/Basic-Lighting
*/
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Shader.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonLightingBasics1App : public App
{
public:
	void setup();
	void update();
	void draw();

	struct ITorus
	{
		vec3 IPosition;
		vec4 IColor;
		ITorus(vec3 pPos, vec4 pCol) :IPosition(pPos), IColor(pCol){}
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

void LessonLightingBasics1App::setup()
{
	getWindow()->setSize(1280, 720);
	mLightColor = Color(1, 1, 0);
	mLightPos = vec3(0,0.75,0);
	mAmbientScale = 1.0f;
	mSpecScale = 1.0f;
	mSpecPow = 32.f;

	auto ad = getAssetPath("basic_lighting_torus.vert");
	
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

	vector<ITorus> cPositions =
	{	
		ITorus(vec3(-1, 0.25, -1), vec4(0.5,0.25,0,1)),
		ITorus(vec3(1, 0.25, -1), vec4(0.25, 0.25, 0.1, 1)),
		ITorus(vec3(-1, 0.25, 1), vec4(0.1, 0.25, 0.25, 1)),
		ITorus(vec3(1, 0.25, 1), vec4(0.0, 0.25, 0.5, 1))
	};

	mTorusMesh = gl::VboMesh::create(geom::Torus().radius(1.0f, 0.99f));
	mInstanceData = gl::Vbo::create(GL_ARRAY_BUFFER, cPositions, GL_STATIC_DRAW);
	mInstanceAttribs.append(geom::CUSTOM_0, 3, sizeof(ITorus), offsetof(ITorus, IPosition), 1);
	mInstanceAttribs.append(geom::CUSTOM_1, 4, sizeof(ITorus), offsetof(ITorus, IColor), 1);
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

	vec3 cEyePos = vec3(0, 0.65f, -2.25f);
	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 100.0f);
	mCamera.lookAt(cEyePos, vec3(0), vec3(0, 1, 0));
	mCamera.setPivotDistance(length(cEyePos));
	mCamUI = CameraUi(&mCamera, getWindow());

	//Now let's set up our parameter window
	//There's really not too much to it at this point, just
	//create the object and call addParam with a name and a pointer
	mGUI = params::InterfaceGl::create("Params", vec2(200, 200));
	mGUI->addParam("Light Color", &mLightColor);
	mGUI->addParam("Ambient Strength", &mAmbientScale);
	mGUI->addParam("Specular Strength", &mSpecScale);
	mGUI->addParam("Specular Power", &mSpecPow);

	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void LessonLightingBasics1App::update()
{
}

void LessonLightingBasics1App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::setMatrices(mCamera);
	
	mPlaneBatch->draw();

	mLightBatch->getGlslProg()->uniform("LightColor", mLightColor);
	mLightBatch->draw();

	mTorusBatch->getGlslProg()->uniform("ViewDirection", mCamera.getViewDirection());
	mTorusBatch->getGlslProg()->uniform("LightColor", mLightColor);
	mTorusBatch->getGlslProg()->uniform("AmbientScale", mAmbientScale);
	mTorusBatch->getGlslProg()->uniform("SpecularScale", mSpecScale);
	mTorusBatch->getGlslProg()->uniform("SpecularPower", mSpecPow);
	mTorusBatch->drawInstanced(4);

	gl::setMatricesWindow(getWindowSize());
	mGUI->draw();
}

CINDER_APP( LessonLightingBasics1App, RendererGl )
