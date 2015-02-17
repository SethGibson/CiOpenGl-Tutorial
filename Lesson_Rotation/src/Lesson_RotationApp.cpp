#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson_RotationApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void Lesson_RotationApp::setup()
{
}

void Lesson_RotationApp::mouseDown( MouseEvent event )
{
}

void Lesson_RotationApp::update()
{
}

void Lesson_RotationApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( Lesson_RotationApp, RendererGl )
