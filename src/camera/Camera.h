/*
 * Camera.h
 *
 *  Created on: 18 de nov de 2015
 *      Author: cassiano
 */

#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

#ifndef CAMERA_CAMERA_H_
#define CAMERA_CAMERA_H_

static const float TO_RAD = M_PI / 180.0;

//namespace camera {

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

	GLfloat look_to_x;
	GLfloat look_to_y;
	GLfloat look_to_z;

	GLfloat horizontal_angle;
	GLfloat vertical_angle;
};

//} /* namespace camera */

#endif /* CAMERA_CAMERA_H_ */
