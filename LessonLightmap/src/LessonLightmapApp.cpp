#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonLightmapApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void LessonLightmapApp::setup()
{
}

void LessonLightmapApp::mouseDown( MouseEvent event )
{
}

void LessonLightmapApp::update()
{
}

void LessonLightmapApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( LessonLightmapApp, RendererGl )
