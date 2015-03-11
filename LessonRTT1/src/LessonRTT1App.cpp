#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LessonRTT1App : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void LessonRTT1App::setup()
{
}

void LessonRTT1App::mouseDown( MouseEvent event )
{
}

void LessonRTT1App::update()
{
}

void LessonRTT1App::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( LessonRTT1App, RendererGl )
