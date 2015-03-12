#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/GeomIo.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonInstancingApp : public App
{
public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	struct CioParticle
	{
		vec3 IPosition;
		vec4 IColor;
		float ISize;

		CioParticle(vec3 pPos, vec4 pColor, float pSize) :IPosition(pPos), IColor(pColor), ISize(pSize){}
	};

	struct CioIVertex
	{
		vec3 VPosition;
		vec2 VUV;

		CioIVertex(vec3 pPos, vec2 pUV) :VPosition(pPos), VUV(pUV){}
	};

private:
	gl::VboRef mParticleData, mInstMeshData;
	gl::VboMeshRef mVboMesh;
	geom::BufferLayout mParticleLayout, mInstMeshLayout;
	gl::BatchRef mParticleBatch;
	gl::GlslProgRef mParticleShader;
	gl::TextureRef mTexRgb;

	CameraPersp mCamera;

};

void LessonInstancingApp::setup()
{
	mTexRgb = gl::Texture::create(loadImage(loadAsset("texture.png")));
	try
	{
		mParticleShader = gl::GlslProg::create(loadAsset("inst_vert.glsl"), loadAsset("inst_frag.glsl"));
	}
	catch (const gl::GlslProgExc &e)
	{
		console() << "Error loading shaders: " << endl;
		console() << e.what() << endl;
		quit();
	}
	vector<CioIVertex> cInstVerts =
	{
		CioIVertex(vec3(0.25, 0.25, 0.0),	vec2(1.0, 1.0)),
		CioIVertex(vec3(-0.25, 0.25, 0.0),	vec2(0.0, 1.0)),
		CioIVertex(vec3(-0.25, -0.25, 0.0),	vec2(0.0, 0.0)),
		CioIVertex(vec3(0.25, 0.25, 0.0),	vec2(1.0, 1.0)),
		CioIVertex(vec3(-0.25, -0.25, 0.0),	vec2(0.0, 0.0)),
		CioIVertex(vec3(0.25, -0.25, 0.0),	vec2(1.0, 0.0))
	};

	mInstMeshData = gl::Vbo::create(GL_ARRAY_BUFFER, cInstVerts, GL_STATIC_DRAW);
	mInstMeshLayout.append(geom::Attrib::POSITION, 3, sizeof(CioIVertex), offsetof(CioIVertex, VPosition));
	mInstMeshLayout.append(geom::Attrib::TEX_COORD_0, 2, sizeof(CioIVertex), offsetof(CioIVertex, VUV));
	mVboMesh = gl::VboMesh::create(6, GL_TRIANGLES, { { mInstMeshLayout, mInstMeshData } });

	vector<CioParticle> cParticles =
	{
		CioParticle(vec3(-2.0,2.0,0.0),		vec4(1,0,0,1), 0.5f),
		CioParticle(vec3(2.0,2.0,0.0),		vec4(0,1,0,1), 1.0f),
		CioParticle(vec3(2.0,-2.0,0.0),		vec4(0,0,1,1), 1.2f),
		CioParticle(vec3(-2.0,-2.0,0.0),	vec4(1,1,0,1), 1.5f)
	};
	mParticleData = gl::Vbo::create(GL_ARRAY_BUFFER, cParticles.size()*sizeof(CioParticle), cParticles.data(), GL_STATIC_DRAW);
	mParticleLayout.append(geom::Attrib::CUSTOM_0, 3, sizeof(CioParticle), offsetof(CioParticle, IPosition), 1);
	mParticleLayout.append(geom::Attrib::CUSTOM_1, 4, sizeof(CioParticle), offsetof(CioParticle, IColor), 1);
	mParticleLayout.append(geom::Attrib::CUSTOM_2, 1, sizeof(CioParticle), offsetof(CioParticle, ISize), 1);
	
	mVboMesh->appendVbo(mParticleLayout, mParticleData);
	mParticleBatch = gl::Batch::create(mVboMesh, mParticleShader, { { geom::Attrib::CUSTOM_0, "iPosition" }, { geom::Attrib::CUSTOM_1, "iColor" }, { geom::Attrib::CUSTOM_2, "iSize" }});

	mCamera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 100.0f);
	mCamera.lookAt(vec3(0, 0, 3), vec3(0), vec3(0, 1, 0));
}

void LessonInstancingApp::mouseDown( MouseEvent event )
{
}

void LessonInstancingApp::update()
{
}

void LessonInstancingApp::draw()
{
	gl::clear( Color( 0.1f, 0.15f, 0.25f ) ); 
	gl::setMatrices(mCamera);
	
	gl::ScopedTextureBind cTexture(mTexRgb);
	mParticleBatch->drawInstanced(4);
}

CINDER_APP( LessonInstancingApp, RendererGl )
