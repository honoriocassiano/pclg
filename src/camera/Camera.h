/*
 * Camera.h
 *
 *  Created on: 18 de nov de 2015
 *      Author: cassiano
 */

#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <glm/glm.hpp>

#define DEBUG_CAMERA 0

#ifndef CAMERA_CAMERA_H_
#define CAMERA_CAMERA_H_

static const float TO_RAD = M_PI / 180.0;

class Camera {
public:
	Camera(GLfloat x_position, GLfloat y_position, GLfloat z_position,
			GLfloat horizontal_angle, GLfloat vertical_angle);
	virtual ~Camera();

	void move(GLfloat delta_front_back, GLfloat delta_left_right);
	void rotate(GLfloat delta_horizontal_angle, GLfloat delta_vertical_angle);

	void update(float time);

private:
	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLfloat look_vector_x;
	GLfloat look_vector_y;
	GLfloat look_vector_z;

	GLfloat horizontal_angle;
	GLfloat vertical_angle;
};

#endif /* CAMERA_CAMERA_H_ */
