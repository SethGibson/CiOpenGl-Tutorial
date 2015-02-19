#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/GeomIo.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/MayaCamUI.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonIndexedVBODynamicApp : public AppNative
{
public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void update() override;
	void draw() override;

	void populateBuffers(bool pInit=true);

	gl::VboRef mPositionData, mColorData, mIndexData;
	gl::VboMeshRef mVboMesh;
	geom::BufferLayout mPositionLayout, mColorLayout;
	gl::BatchRef mBatch;
	gl::GlslProgRef mGlsl;

	CameraPersp mCamera;
	MayaCamUI mMayaCam;

	int mMaxX, mMaxY, mMaxVerts;
	vector<vec3> mVerts;
	vector<vec4> mColors;
	vector<uint32_t> mIndices;
};

void LessonIndexedVBODynamicApp::setup()
{
	mMaxX = 16;
	mMaxY = 16;
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

	populateBuffers(true);
	mBatch = gl::Batch::create(mVboMesh, mGlsl);

	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 100.0f);
	mCamera.lookAt(vec3(0, 0, 5), vec3(0), vec3(0, 1, 0));
	mCamera.setCenterOfInterestPoint(vec3(0));
	mMayaCam.setCurrentCam(mCamera);
}

void LessonIndexedVBODynamicApp::populateBuffers(bool pInit)
{
	mVerts.clear();
	mColors.clear();
	mIndices.clear();

	for (int vy = 0; vy < mMaxY; ++vy)
	{
		for (int vx = 0; vx < mMaxX; ++vx)
		{
			float cX = lmap<float>(vx, 0, mMaxX - 1, 1.0f, -1.0f);
			float cY = lmap<float>(vy, 0, mMaxY - 1, 1.0f, -1.0f);
			float cZ = math<float>::sin((vx + getElapsedSeconds()))*0.5f;
			mVerts.push_back(vec3(cX, cY, cZ));

			float cR = lmap<float>(vx, 0, mMaxX - 1, 0.0f, 1.0f);
			float cG = lmap<float>(vy, 0, mMaxY - 1, 0.0f, 1.0f);
			float cB = math<float>::sin(vy);
			cB = (cB + 1.0f)*0.5f;
			mColors.push_back(vec4(cR, cG, cB, 1.0));
		}
	}

	mMaxVerts = mVerts.size();

	for (int cid = 0; cid < mMaxVerts; ++cid)
	{
		int n = cid;
		int n_1 = n + 1;
		int n_x = n + mMaxX;
		int n_x1 = n + mMaxX + 1;

		if ((n >= 0 && n < mMaxVerts) &&
			(n_1 >= 0 && n_1 < mMaxVerts) &&
			(n_x >= 0 && n_x < mMaxVerts))
		{
			if (mVerts.at(n_1).x <= mVerts.at(n).x)
			{
				mIndices.push_back(n);
				mIndices.push_back(n_1);
				mIndices.push_back(n_x);
			}
		}

		if ((n_1 >= 0 && n_1 < mMaxVerts) &&
			(n_x1 >= 0 && n_x1 < mMaxVerts) &&
			(n_x >= 0 && n_x < mMaxVerts))
		{
			if (mVerts.at(n_x1).x <= mVerts.at(n_x).x)
			{
				mIndices.push_back(n_1);
				mIndices.push_back(n_x1);
				mIndices.push_back(n_x);
			}
		}
	}

	if (pInit)
	{
		mPositionData = gl::Vbo::create(GL_ARRAY_BUFFER, mVerts.size()*sizeof(vec3), mVerts.data(), GL_DYNAMIC_DRAW);
		mPositionLayout.append(geom::Attrib::POSITION, 3, 0, 0);

		mColorData = gl::Vbo::create(GL_ARRAY_BUFFER, mColors.size()*sizeof(vec4), mColors.data(), GL_DYNAMIC_DRAW);
		mColorLayout.append(geom::Attrib::COLOR, 4, 0, 0);

		mIndexData = gl::Vbo::create(GL_ELEMENT_ARRAY_BUFFER, mIndices.size()*sizeof(uint32_t), mIndices.data(), GL_DYNAMIC_DRAW);

	}
	else
	{
		mPositionData = gl::Vbo::create(GL_ARRAY_BUFFER, mVerts, GL_DYNAMIC_DRAW);
		mColorData = gl::Vbo::create(GL_ARRAY_BUFFER, mColors, GL_DYNAMIC_DRAW);
		mIndexData = gl::Vbo::create(GL_ELEMENT_ARRAY_BUFFER, mIndices, GL_DYNAMIC_DRAW);
		mVboMesh = gl::VboMesh::create(mVerts.size(), GL_TRIANGLES, { { mPositionLayout, mPositionData }, { mColorLayout, mColorData } }, mIndices.size(), GL_UNSIGNED_INT, mIndexData);
	}
	mVboMesh = gl::VboMesh::create(mVerts.size(), GL_TRIANGLES, { { mPositionLayout, mPositionData }, { mColorLayout, mColorData } }, mIndices.size(), GL_UNSIGNED_INT, mIndexData);
	if (!pInit)
		mBatch->replaceVboMesh(mVboMesh);
}

void LessonIndexedVBODynamicApp::mouseDown(MouseEvent event)
{
	mMayaCam.mouseDown(event.getPos());
}

void LessonIndexedVBODynamicApp::mouseDrag(MouseEvent event)
{
	mMayaCam.mouseDrag(event.getPos(), event.isLeftDown(), false, event.isRightDown());
}

void LessonIndexedVBODynamicApp::update()
{
	mMaxX = randInt(4, 16);
	mMaxY = randInt(4, 16);
	int r = mMaxX % 2;
	if (r > 0)mMaxX += r;
	r = mMaxY % 2;
	if (r > 0)mMaxY += r;

	populateBuffers(false);
}

void LessonIndexedVBODynamicApp::draw()
{
	gl::clear(Color(0.1f, 0.15f, 0.25f));
	gl::setMatrices(mMayaCam.getCamera());
	gl::enableWireframe();
	mBatch->draw();
	gl::disableWireframe();
	gl::setMatricesWindow(getWindowSize());
	gl::drawString("Frames Per Second: " + to_string(getAverageFps()), vec2(10));
}

CINDER_APP_NATIVE(LessonIndexedVBODynamicApp, RendererGl)
