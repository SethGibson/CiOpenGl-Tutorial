#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson_InstancingApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void Lesson_InstancingApp::setup()
{
}

void Lesson_InstancingApp::mouseDown( MouseEvent event )
{
}

void Lesson_InstancingApp::update()
{
}

void Lesson_InstancingApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( Lesson_InstancingApp, RendererGl )
