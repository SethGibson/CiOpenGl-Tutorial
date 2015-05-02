#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/Texture.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonBillboardsApp : public App
{
public:
	void setup();
	void mouseDown(MouseEvent event);
	void update();
	void draw();

private:
	gl::BatchRef		mBatch;
	gl::VboRef			mInstanceData;
	geom::BufferLayout	mInstanceAttribs;

	gl::VboMeshRef		mBillboardMesh;
	gl::GlslProgRef		mShader;

	gl::Texture2dRef	mTexRgb;

	CameraPersp			mCamera;
	CameraUi			mCamUI;
};

void LessonBillboardsApp::setup()
{
	vector<vec3> cPositions;

	//Let's create a bunch of positions for our flower petals
	//standard vbo instancing here
	for (int i = 0; i < 1000; ++i)
	{
		cPositions.push_back(vec3(randFloat(-10.f, 10.f), randFloat(-10.f, 10.f), randFloat(-10.f, 10.f)));
	}

	mShader = gl::GlslProg::create(loadAsset("billboard_vert.glsl"), loadAsset("billboard_frag.glsl"));

	mInstanceData = gl::Vbo::create(GL_ARRAY_BUFFER, cPositions, GL_STATIC_DRAW);
	mInstanceAttribs.append(geom::Attrib::CUSTOM_0, 3, 0, 0, 1);
	mBillboardMesh = gl::VboMesh::create(geom::Plane().axes(vec3(0, 1, 0), vec3(1, 0, 0)).size(vec2(1)));
	mBillboardMesh->appendVbo(mInstanceAttribs, mInstanceData);
	mBatch = gl::Batch::create(mBillboardMesh, mShader, { { geom::CUSTOM_0, "i_Position" } });

	//make sure our texture file lives in the assets directory
	//this is a 256x256 png with an alpha channel
	mTexRgb = gl::Texture2d::create(loadImage(loadAsset("tex_petal.png")));

	gl::disable(GL_DEPTH_TEST);
	gl::disableDepthWrite();
	gl::enableAlphaBlending();

	getWindow()->setSize(1280, 720);
	setFrameRate(60);

	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 100.0f);
	mCamera.setEyePoint(vec3(0, 0, -40));
	mCamera.setViewDirection(vec3(0, 0, 1));
	mCamera.setPivotDistance(40);
	mCamUI = CameraUi(&mCamera, getWindow(), 0);
}

void LessonBillboardsApp::mouseDown(MouseEvent event)
{
}

void LessonBillboardsApp::update()
{
}

void LessonBillboardsApp::draw()
{
	// clear out the window with black
	gl::clear(Color(0, 0, 0));
	gl::color(Color::white());
	vec3 cCameraRight, cCameraUp;

	/*
	Billboarding in theory is pretty simple:
	We need to know what the camera's up and right vectors are, which Cinder gives us
	Once we have those, we transform the instance mesh's vertex positions by those vectors
	so the mesh is ALWAYS facing the camera (see billboard_vert.glsl for more comments)
	*/
	mCamUI.getCamera().getBillboardVectors(&cCameraRight, &cCameraUp);

	//Now we pass in the camera vectors as shader uniforms
	mBatch->getGlslProg()->uniform("u_CameraUp", cCameraUp);
	mBatch->getGlslProg()->uniform("u_CameraRight", cCameraRight);
	mBatch->getGlslProg()->uniform("u_SamplerRGB", 0);
	mTexRgb->bind();

	//Then we draw our instances as usual
	gl::setMatrices(mCamUI.getCamera());
	mBatch->drawInstanced(1000);
	mTexRgb->unbind();

	//and let's draw some debug stuff just for fun
	gl::drawStrokedCube(vec3(0), vec3(20));
	gl::color(Color(1, 0, 0));
	gl::drawLine(vec3(0), vec3(3, 0, 0));
	gl::color(Color(0, 1, 0));
	gl::drawLine(vec3(0), vec3(0, 3, 0));
	gl::color(Color(0, 0, 1));
	gl::drawLine(vec3(0), vec3(0, 0, 3));

}

CINDER_APP(LessonBillboardsApp, RendererGl)