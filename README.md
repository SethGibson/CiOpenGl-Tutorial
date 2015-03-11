# CiOpenGl-Tutorial
**UPDATE (2015.03.10):** Added LightingBasic1

Gettings started with Cinder glNext(0.9.0?)'s new OpenGL API.

_DISCLAIMER: This project should be considered experimental until expressly stated otherwise, as Cinder's API is subject to change!_

This repo is a port of various modern OpenGL tutorials to Cinder, both for learning purposes and as stubs for other work.<br/>
Original content can be found at/taken from:<br/>

* [OpenGL-Tutorial.org](http://www.opengl-tutorial.org)
* [OGLDev's Modern OpenGL Tutorials](http://ogldev.atspace.co.uk/)
* [Learn OpenGL](http://learnopengl.com/)
* My brain

## Installation Notes
* Clone this anywhere on your system and add an environment variable called **CINDER_DEV**, which should point to the top level of your glNext install, e.g. **C:\dev\libraries\Cinder** or something like that.  The environment variable is optional, but be sure to change the VS projects to point to your Cinder install otherwise.
* Each project has an individual solution, or you can open the included **CiOpenGl-Tutorial.sln**.

## Lessons
* Lesson01: Triangle
* Lesson02: Camera
* Lesson03: 3D Shapes, Vertex Attributes
* Lesson04: Basic Texturing
* Lesson04b: Interleaved Vertex Attributes
* Lesson05: Cinder Interactive Camera (Cinder::MayaCamUI)
* LessonIndexedVBO: Drawing VBOMesh with Indices
* LessonIndexedVBODynamic: Drawing VBOMesh with Dynamic Attributes
* LessonInstancing: Drawing Instanced Geometry with per-Instance Attributes
* LessonLightingBasic1: Diffuse+Ambient+Specular


### Coming Soon (Subject to Change)
* LessonVBORanged: Dynamic VBOs using ranged buffers
* LessonVBOSubBuffer: Dynamic VBOs using sub buffering
* LessonInstancingDynamic: Instanced Geometry with Dynamic per-Instance Attributes
* LessonLightingBasic2: Diffuse+Ambient+Specular+Normal Mapping
* LessonRTT1: Shadow Maps
* LessonRTT2: Skyboxes
* LessonRTT3: FSFX
* Various things involving depth-based point clouds

Questions, comments, suggestions to [my inbox](mailto:seth.gibson1@gmail.com).  Also, I love PRs.
