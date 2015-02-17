#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson06App : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void Lesson06App::setup()
{
}

void Lesson06App::mouseDown( MouseEvent event )
{
}

void Lesson06App::update()
{
}

void Lesson06App::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( Lesson06App, RendererGl )
