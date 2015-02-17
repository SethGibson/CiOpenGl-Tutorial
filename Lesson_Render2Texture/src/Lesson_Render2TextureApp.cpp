#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson_Render2TextureApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void Lesson_Render2TextureApp::setup()
{
}

void Lesson_Render2TextureApp::mouseDown( MouseEvent event )
{
}

void Lesson_Render2TextureApp::update()
{
}

void Lesson_Render2TextureApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( Lesson_Render2TextureApp, RendererGl )
