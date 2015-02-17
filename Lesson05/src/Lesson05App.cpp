#/* Cinder OpenGL-Tutorial - Cinder GL tutorials based on www.opengl-tutorial.org

Lesson 05: Simple camera and mouse input
Original Tutorial:
Well, actually this one only follows opengl-tutorial.org in topic.

Let's set up Cinder's MayaCamUI to get some simple mouse interaction
*/

#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/MayaCamUI.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson05App : public AppNative {
public:
	void	setup() override;
	void	update() override;
	void	draw() override;
	void	mouseDown(MouseEvent pEvent) override;
	void	mouseDrag(MouseEvent pEvent) override;

	struct CioVertex
	{
		vec3 vPosition;
		vec4 vColor;
		vec2 vUV;

		CioVertex(vec3 pPos, vec4 pColor, vec2 pUV) : vPosition(pPos), vColor(pColor), vUV(pUV){}
	};

	gl::GlslProgRef		mGlsl;
	gl::VboRef			mVertexData;
	geom::BufferLayout	mVertexLayout;
	gl::VboMeshRef		mMesh;
	gl::BatchRef		mBatch;
	gl::Texture2dRef	mTexture;

	CameraPersp			mCamera;
	MayaCamUI			mMayaCam;
};

void Lesson05App::setup()
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

	vector<CioVertex> cVertList =
	{
		CioVertex(vec3(1.0f, 1.0f, 0.0f), vec4(0.583f, 0.771f, 0.014f, 1.0f), vec2(1.0, 1.0)),
		CioVertex(vec3(-1.0f, 1.0f, 0.0f), vec4(0.609f, 0.115f, 0.436f, 1.0f), vec2(0.0, 1.0)),
		CioVertex(vec3(-1.0f, -1.0f, 0.0f), vec4(0.327f, 0.483f, 0.844f, 1.0f), vec2(0.0, 0.0)),
		CioVertex(vec3(1.0f, 1.0f, 0.0f), vec4(0.822f, 0.569f, 0.201f, 1.0f), vec2(1.0, 1.0)),
		CioVertex(vec3(-1.0f, -1.0f, 0.0f), vec4(0.435f, 0.602f, 0.223f, 1.0f), vec2(0.0, 0.0)),
		CioVertex(vec3(1.0f, -1.0f, 0.0f), vec4(0.310f, 0.747f, 0.185f, 1.0f), vec2(1.0, 0.0))
	};

	mVertexData = gl::Vbo::create(GL_ARRAY_BUFFER, cVertList, GL_STATIC_DRAW);
	mVertexLayout.append(geom::Attrib::POSITION, 3, sizeof(CioVertex), offsetof(CioVertex, vPosition));
	mVertexLayout.append(geom::Attrib::COLOR, 4, sizeof(CioVertex), offsetof(CioVertex, vColor));
	mVertexLayout.append(geom::Attrib::TEX_COORD_0, 2, sizeof(CioVertex), offsetof(CioVertex, vUV));

	mMesh = gl::VboMesh::create(6, GL_TRIANGLES, { { mVertexLayout, mVertexData } });
	mBatch = gl::Batch::create(mMesh, mGlsl);

	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 100.0f);
	mCamera.lookAt(vec3(0, -3, 3), vec3(0), vec3(0, 1, 0));
	mCamera.setCenterOfInterestPoint(vec3(0));
	mMayaCam.setCurrentCam(mCamera);
}

void Lesson05App::mouseDown(MouseEvent pEvent)
{
	mMayaCam.mouseDown(pEvent.getPos());
}

void Lesson05App::mouseDrag(MouseEvent pEvent)
{
	mMayaCam.mouseDrag(pEvent.getPos(), pEvent.isLeftDown(), false, pEvent.isRightDown());
}

void Lesson05App::update()
{
}

void Lesson05App::draw()
{
	gl::enableDepthRead();
	gl::enableDepthWrite();

	gl::clear(Color(0.1f, 0.15f, 0.25f));
	gl::setMatrices(mMayaCam.getCamera());
	mTexture->bind();
	mBatch->draw();
}

CINDER_APP_NATIVE( Lesson05App, RendererGl )
