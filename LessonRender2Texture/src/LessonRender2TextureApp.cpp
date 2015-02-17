#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonRender2TextureApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void LessonRender2TextureApp::setup()
{
}

void LessonRender2TextureApp::mouseDown( MouseEvent event )
{
}

void LessonRender2TextureApp::update()
{
}

void LessonRender2TextureApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( LessonRender2TextureApp, RendererGl )
