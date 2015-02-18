#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/GeomIo.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonInstancingApp : public AppNative
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
	gl::BatchRef mParticleDraw;
	gl::GlslProgRef mParticleShader;

};

void LessonInstancingApp::setup()
{
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
		CioIVertex(vec3(1.0f, 1.0f, 0.0f), vec4(0.583f, 0.771f, 0.014f, 1.0f), vec2(1.0, 1.0)),
		CioIVertex(vec3(-1.0f, 1.0f, 0.0f), vec4(0.609f, 0.115f, 0.436f, 1.0f), vec2(0.0, 1.0)),
		CioIVertex(vec3(-1.0f, -1.0f, 0.0f), vec4(0.327f, 0.483f, 0.844f, 1.0f), vec2(0.0, 0.0)),
		CioIVertex(vec3(1.0f, 1.0f, 0.0f), vec4(0.822f, 0.569f, 0.201f, 1.0f), vec2(1.0, 1.0)),
		CioIVertex(vec3(-1.0f, -1.0f, 0.0f), vec4(0.435f, 0.602f, 0.223f, 1.0f), vec2(0.0, 0.0)),
		CioIVertex(vec3(1.0f, -1.0f, 0.0f), vec4(0.310f, 0.747f, 0.185f, 1.0f), vec2(1.0, 0.0))
	};
	mInstMeshData = gl::Vbo::create(GL_ARRAY_BUFFER, cInstVerts, GL_STATIC_DRAW);
	mInstMeshLayout.append(geom::Attrib::POSITION, 3, sizeof(CioIVertex), offsetof(CioIVertex, VPosition));
	mInstMeshLayout.append(geom::Attrib::TEX_COORD_0, 2, sizeof(CioIVertex), offsetof(CioIVertex, VUV));
	mVboMesh = gl::VboMesh::create(6, GL_TRIANGLES, { { mInstMeshLayout, mInstMeshData } });

	vector<CioParticle> cParticles =
	{
		CioParticle(vec3(0), vec4(0), 0.0f),
		CioParticle(vec3(0), vec4(0), 0.0f),
		CioParticle(vec3(0), vec4(0), 0.0f),
		CioParticle(vec3(0), vec4(0), 0.0f)
	};
	mParticleData = gl::Vbo::create(GL_ARRAY_BUFFER, (cParticles.size()*sizeof(CioParticle), GL_STATIC_DRAW));
	mParticleLayout.append(geom::Attrib::CUSTOM_0, 3, sizeof(CioParticle), offsetof(CioParticle, IPosition), 1);
	mParticleLayout.append(geom::Attrib::CUSTOM_1, 4, sizeof(CioParticle), offsetof(CioParticle, IColor), 1);
	mParticleLayout.append(geom::Attrib::CUSTOM_2, 1, sizeof(CioParticle), offsetof(CioParticle, ISize), 1);
	
	mVboMesh->appendVbo(mParticleLayout, mParticleData);
}

void LessonInstancingApp::mouseDown( MouseEvent event )
{
}

void LessonInstancingApp::update()
{
}

void LessonInstancingApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( LessonInstancingApp, RendererGl )
