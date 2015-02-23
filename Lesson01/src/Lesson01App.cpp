/* Cinder OpenGL-Tutorial - Cinder GL tutorials based on www.opengl-tutorial.org

Lesson 01: The first triangle
Original Tutorial: 
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
*/

#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Lesson01App : public AppNative {
public:
	void	setup() override;
	void	update() override;
	void	draw() override;

	gl::GlslProgRef		mGlsl;
	gl::VboRef mShapeVbo;
	geom::BufferLayout mShapeLayout;
	gl::VboMeshRef mShapeMesh;
	gl::BatchRef		mBatch;
};

void Lesson01App::setup()
{
	getWindow()->setSize(1024, 768);

	//	Load our shaders first.  In this tutorial series, everything uses shaders
	//		A. So we can practice writing shaders
	//		B. So we get comfortable with cinder's new shader API
	//	We'll skip over cinder's stock shader functionality because it probably
	//	shouldn't be used for production, and again, we should get comfortable
	//	with the idea that all of our content needs shaders and at the very least
	//	we should write our own library of stock shaders
	try
	{
		mGlsl = gl::GlslProg::create(loadAsset("simple_vert.glsl"), loadAsset("simple_frag.glsl"));
	}

	//	cinder defines a few different glsl exceptions that derive from the base GlslProgExc class
	//	so we'll catch them all here.  Might seem a bit heavy handed, but e.what() will actually
	//	provide all the info you should need for simple debugging.  
	catch (const gl::GlslProgExc &e)
	{
		console() << "Error loading shaders:" << endl;
		console() << e.what() << endl;
		quit();
	}

	//	First we'll set up our buffer data.  This is analogous-ish to:
	//		static const GLfloat g_vertex_buffer_data[] = {
	//			-1.0f, -1.0f, 0.0f,
	//			1.0f, -1.0f, 0.0f,
	//			0.0f, 1.0f, 0.0f,
	//		};
	//		GLuint vertexbuffer;
	//		glGenBuffers(1, &vertexbuffer);
	//		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	float cWidth = (float)getWindowWidth();
	float cHeight = (float)getWindowHeight();
	vector<vec3> cVertices = { vec3(0.0, cHeight, 0.0),
								vec3(cWidth, cHeight, 0.0),
								vec3(cWidth / 2, 0.0, 0.0) };
	mShapeVbo = gl::Vbo::create(GL_ARRAY_BUFFER, cVertices, GL_STATIC_DRAW);

	//	Now we'll set add attributes and set up our draw object.  This is analogous-ish to:
	//		glEnableVertexAttribArray(0);
	//		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	//
	//	Note how appending to a Vbo::Layout maps-ish to a glVertexAttribPointerCall:
	//		glVertexAttribPointer(	index,		size,		datatype,	normalize,	stride,	offset)
	//		mShapeLayout.append(	attribute,	datatype,	size,		stride,		offset)
	mShapeLayout.append(geom::Attrib::POSITION, geom::DataType::FLOAT, 3, sizeof(vec3), 0);

	//	Lastly, set up our draw objects.  Under the hood, we're actually "drawing" the vbomesh
	//	(See Batch.cpp for details), the Batch manages all the other things like vertex array objects,
	//	attribute mapping, etc.  If you're famililar with pre 0.9.0/glNext Cinder, Batch is where
	//	shader binding and other drawing related ops take place (did you notice that we don't call
	//	mGlsl->bind() directly?)
	mShapeMesh = gl::VboMesh::create(3, GL_TRIANGLES, { { mShapeLayout, mShapeVbo } });
	mBatch = gl::Batch::create(mShapeMesh, mGlsl);
}

void Lesson01App::update()
{
}

void Lesson01App::draw()
{
	gl::clear(Color(0, 0, 0.15f));
	gl::setMatricesWindowPersp(getWindowSize());

	//	Finally, draw our triangle!  This is where we call glDrawArrays or
	//	glDrawElements, depending on how our batch is set up initially.  In this case,
	//	we glDrawArrays().
	mBatch->draw();
}

CINDER_APP_NATIVE( Lesson01App, RendererGl )