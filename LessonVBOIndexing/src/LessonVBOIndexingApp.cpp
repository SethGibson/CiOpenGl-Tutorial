#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonVBOIndexingApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void LessonVBOIndexingApp::setup()
{
}

void LessonVBOIndexingApp::mouseDown( MouseEvent event )
{
}

void LessonVBOIndexingApp::update()
{
}

void LessonVBOIndexingApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( LessonVBOIndexingApp, RendererGl )
