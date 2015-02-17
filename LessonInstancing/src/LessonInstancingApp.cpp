#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonInstancingApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void LessonInstancingApp::setup()
{
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
