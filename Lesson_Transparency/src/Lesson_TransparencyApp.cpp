#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson_TransparencyApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void Lesson_TransparencyApp::setup()
{
}

void Lesson_TransparencyApp::mouseDown( MouseEvent event )
{
}

void Lesson_TransparencyApp::update()
{
}

void Lesson_TransparencyApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( Lesson_TransparencyApp, RendererGl )
