#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson_NormalMappingApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void Lesson_NormalMappingApp::setup()
{
}

void Lesson_NormalMappingApp::mouseDown( MouseEvent event )
{
}

void Lesson_NormalMappingApp::update()
{
}

void Lesson_NormalMappingApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( Lesson_NormalMappingApp, RendererGl )
