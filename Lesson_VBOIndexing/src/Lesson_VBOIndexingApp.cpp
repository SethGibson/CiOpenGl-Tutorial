#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson_VBOIndexingApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void Lesson_VBOIndexingApp::setup()
{
}

void Lesson_VBOIndexingApp::mouseDown( MouseEvent event )
{
}

void Lesson_VBOIndexingApp::update()
{
}

void Lesson_VBOIndexingApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( Lesson_VBOIndexingApp, RendererGl )
