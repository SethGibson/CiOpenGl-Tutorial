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
		vec3 PPosition;
		vec4 PColor;
		float PSize;
	};

	struct CioIVertex
	{
		vec3 VPosition;
		vec2 VUV;
	};

private:
	gl::VboRef mParticleData, mInstanceData;
	geom::BufferLayout mParticleLayout, mInstanceLayout;
	gl::BatchRef mParticleDraw;
	gl::GlslProgRef mParticleShader;

};

void LessonInstancingApp::setup()
{
	vector<CioParticle> cParticles;
	vector<CioIVertex> cInstVerts;

	mParticleData = gl::Vbo::create(GL_ARRAY_BUFFER, cParticles, GL_STATIC_DRAW);
	mParticleLayout.append(geom::Attrib::CUSTOM_0, 3, sizeof(CioParticle), offsetof(CioParticle, PPosition));
	mParticleLayout.append(geom::Attrib::CUSTOM_1, 4, sizeof(CioParticle), offsetof(CioParticle, PColor));
	mParticleLayout.append(geom::Attrib::CUSTOM_2, 1, sizeof(CioParticle), offsetof(CioParticle, PSize));

	mInstanceData = gl::Vbo::create(GL_ARRAY_BUFFER, cParticles, GL_STATIC_DRAW);
	//mInstanceLayout.append(geom::Attrib::POSITION)
	//mInstanceLayout.append(geom::Attrib::TEX_COORD_0);
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
