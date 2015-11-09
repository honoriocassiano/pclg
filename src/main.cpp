#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <string>

#include "shaders.h"
#include "textfile.h"
#include "shader/ShaderManager.h"
#include "noise/Perlin.h"

noise::Perlin * perlin_noise;

GLint loc_time;
GLint loc_octaves;
GLuint v,f,f2,p;

float lpos[4] = {1.0,0.0,1.0,0.0};

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,100);
	glMatrixMode(GL_MODELVIEW);
}

float a = 1;

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0,1.0,5.0,
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glRotatef(a,0,1,0);

	perlin_noise->update(a);

	glutSolidTeapot(1);
	a+=0.001;

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        std::cout << "glError in file " << file << " @ line" << line << ":" << gluErrorString(glErr) << std::endl;
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}


void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		std::cout << infoLog;

        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		std::cout << infoLog;

        free(infoLog);
    }
}



void setShaders() {
	perlin_noise->show();

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Procedural Cloud Generator");

	perlin_noise = new noise::Perlin(20);

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_CULL_FACE);

	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		std::cout << "Ready for OpenGL 2.0\n";
	else {
		std::cout << "OpenGL 2.0 not supported!\n";
		exit(1);
	}

	setShaders();

	glutMainLoop();

	return 0;
}

