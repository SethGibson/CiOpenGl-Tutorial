#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson_ShadowmapsApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void Lesson_ShadowmapsApp::setup()
{
}

void Lesson_ShadowmapsApp::mouseDown( MouseEvent event )
{
}

void Lesson_ShadowmapsApp::update()
{
}

void Lesson_ShadowmapsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( Lesson_ShadowmapsApp, RendererGl )
