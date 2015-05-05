#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

int S_NUM_PARTICLES = 1000;
class LessonInstancingAdvancedApp : public App
{
public:
	void setup() override;
	void update() override;
	void draw() override;

	struct Particle
	{
		vec3	mPos;
		vec3	mVel;
		ColorA	mColor;
		int		mLife, mAge;
		float	mRotSpeed;
		float	mSize, mSize_0;

		//We'll use this to store our new per-instance transform
		mat4	mTransform;

		Particle()
		{
			mPos = vec3(0);
			mVel = vec3(randFloat(-0.002f, 0.002f), randFloat(0.004f, 0.01f), randFloat(-0.002f, 0.002f));
			mColor = ColorA(0.f, randFloat(), randFloat(), randFloat(0.1f, 0.75f));
			mRotSpeed = randFloat(-1.f, 1.f);
			mLife = randInt(120, 360);
			mAge = mLife;
			mSize = randFloat(0.1f, 1.0f);
			mSize_0 = mSize;
		}

		void step(float pElapsed, vec3 pAxis)
		{
			mAge--;
			if (mAge > 0)
			{
				//set the matrix to the identitiy
				mTransform = glm::mat4();

				//first we update the position in the usual fashion...
				mPos += mVel;
				mSize = lerp<float>(0, mSize_0, (float)mAge / (float)mLife);
				//now we can generate a model matrix from our position and rotation factors
				mTransform = glm::translate(mTransform, mPos);
				mTransform = glm::rotate(mTransform, mRotSpeed*pElapsed*0.1f, pAxis);
			}
		}
	};

private:
	vector<Particle>	mParticles;
	CameraPersp			mCamera;
	CameraUi			mCamUi;

	gl::BatchRef		mBatch;
	gl::VboRef			mData;
	geom::BufferLayout	mAttribs;
	gl::VboMeshRef		mMesh;
	gl::GlslProgRef		mShader;
};

void LessonInstancingAdvancedApp::setup()
{
	getWindow()->setSize(1280, 720);
	setFrameRate(60.f);

	vec3 cEyePos = vec3(0, 0, 5);
	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 100.0f);
	mCamera.lookAt(cEyePos, vec3(0), vec3(0, 1, 0));
	mCamera.setPivotDistance(length(cEyePos));
	mCamUi = CameraUi(&mCamera, getWindow());

	mParticles.push_back(Particle());
	mShader = gl::GlslProg::create(loadAsset("vert.glsl"), loadAsset("frag.glsl"));
	mData = gl::Vbo::create(GL_ARRAY_BUFFER, mParticles, GL_DYNAMIC_DRAW);

	//	Instead of passing in position as an attribute by itself, 
	//	we pass in the whole transform matrix as an attribute.
	mAttribs.append(geom::CUSTOM_0, 16, sizeof(Particle), offsetof(Particle, mTransform), 1);
	mAttribs.append(geom::CUSTOM_1, 4, sizeof(Particle), offsetof(Particle, mColor), 1);
	mAttribs.append(geom::CUSTOM_2, 1, sizeof(Particle), offsetof(Particle, mSize), 1);

	mMesh = gl::VboMesh::create(geom::Plane().size(vec2(0.25)).axes(vec3(1, 0, 0), vec3(0, 1, 0)));
	mMesh->appendVbo(mAttribs, mData);

	mBatch = gl::Batch::create(mMesh, mShader, { { geom::CUSTOM_0, "iModelMatrix" }, { geom::CUSTOM_1, "iColor" }, { geom::CUSTOM_2, "iSize" } });

	gl::enableAlphaBlending();
}


void LessonInstancingAdvancedApp::update()
{
	if (mParticles.size() < S_NUM_PARTICLES)
		mParticles.push_back(Particle());

	//	To guarantee that our particles are billboarded and rotating properly,
	//	we need to pass in the camera's view direction vector as our per-instance
	//	rotation axis. View direction is essentially the camera's Z-vector.
	for (auto pit = mParticles.begin(); pit != mParticles.end();)
	{
		pit->step((float)getElapsedFrames(), mCamera.getViewDirection());
		if (pit->mAge <= 0)
			pit = mParticles.erase(pit);
		else
			++pit;
	}

	mData->bufferData(mParticles.size()*sizeof(Particle), mParticles.data(), GL_DYNAMIC_DRAW);
}

void LessonInstancingAdvancedApp::draw()
{
	gl::clear(Color(0, 0, 0));
	gl::setMatrices(mCamera);

	vec3 cRight, cUp;
	mCamera.getBillboardVectors(&cRight, &cUp);
	mBatch->getGlslProg()->uniform("u_CameraRight", cRight);
	mBatch->getGlslProg()->uniform("u_CameraUp", cUp);

	gl::color(Color::white());
	mBatch->drawInstanced(mParticles.size());

	gl::color(Color(1, 0, 0));
	gl::drawLine(vec3(0), vec3(2, 0, 0));
	gl::color(Color(0, 1, 0));
	gl::drawLine(vec3(0), vec3(0, 2, 0));
	gl::color(Color(0, 0, 1));
	gl::drawLine(vec3(0), vec3(0, 0, 2));
}

CINDER_APP(LessonInstancingAdvancedApp, RendererGl)
