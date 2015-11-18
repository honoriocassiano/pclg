#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>

#include "shaders.h"
#include "textfile.h"
#include "shader/ShaderManager.h"
#include "noise/Perlin.h"
#include "sky/SkyDome.h"

#define USE_PERLIN 1
#define DEBUG_CAMERA 0

noise::Perlin * perlin_noise;
sky::SkyDome * skyDome;

static const float TO_RAD = M_PI / 180.0;

float deltha = 0.0;
float theta = 0.0;
float camera_ray = 6;

float prev_deltha = -1.0;
float prev_theta = -1.0;

float x, y, z;

GLint loc_time;
GLint loc_octaves;
GLuint v, f, f2, p;

GLfloat dx = 0.0, dy = 0.0, dz = 0.0;

float lpos[4] = { 1.0, 0.0, 1.0, 0.0 };

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = 1.0 * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 100);
	glMatrixMode(GL_MODELVIEW);
}

float elapsed_time = 1;

void renderScene(void) {

	if (prev_deltha != deltha || prev_theta != theta) {
		float theta_rad = theta * TO_RAD;
		float deltha_rad = deltha * TO_RAD * -1;

		float cos_x_angle = cos(theta_rad);
		float cos_y_angle = cos(deltha_rad);

		float sin_x_angle = sin(theta_rad);
		float sin_y_angle = sin(deltha_rad);

		x = camera_ray * sin_x_angle * sin_y_angle;
		y = camera_ray * cos_x_angle;
		z = camera_ray * sin_x_angle * cos_y_angle;

		if (DEBUG_CAMERA) {
			std::cout << "(x, y, z) => (" << x << ", " << y << ", " << z
					<< ")\n";
		}

		prev_deltha = deltha;
		prev_theta = theta;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glRotatef(elapsed_time, 0, 1, 0);

	elapsed_time += 0.001;

	if (USE_PERLIN) {
		perlin_noise->update(elapsed_time);
	} else {
		skyDome->update(elapsed_time);
	}

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line) {
	//
	// Returns 1 if an OpenGL error occurred, 0 otherwise.
	//
	GLenum glErr;
	int retCode = 0;

	glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		std::cout << "glError in file " << file << " @ line" << line << ":"
				<< gluErrorString(glErr) << std::endl;
		retCode = 1;
		glErr = glGetError();
	}
	return retCode;
}

void printShaderInfoLog(GLuint obj) {
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0) {
		infoLog = (char *) malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		std::cout << infoLog;

		free(infoLog);
	}
}

void printProgramInfoLog(GLuint obj) {
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0) {
		infoLog = (char *) malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		std::cout << infoLog;

		free(infoLog);
	}
}

void specialKeyFuncton(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_UP:
			theta += 1.0;
			break;
		case GLUT_KEY_DOWN:
			theta -= 1.0;
			break;
		case GLUT_KEY_LEFT:
			deltha += 1.0;
			break;
		case GLUT_KEY_RIGHT:
			deltha -= 1.0;
			break;
	}
}

void showPerlin() {

	if (USE_PERLIN) {
		perlin_noise->apply_to(skyDome);
		perlin_noise->show();
	} else {
		skyDome->show();
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Procedural Cloud Generator");

	perlin_noise = new noise::Perlin(20);
	skyDome = new sky::SkyDome(1.5, 20, 5);

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(specialKeyFuncton);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//glEnable(GL_CULL_FACE);

	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		std::cout << "Ready for OpenGL 2.0\n";
	else {
		std::cout << "OpenGL 2.0 not supported!\n";
		exit(1);
	}

	showPerlin();

	glutMainLoop();

	return 0;
}

