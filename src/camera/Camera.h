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

//namespace camera {

class Camera {
public:
	Camera(GLfloat x_position, GLfloat y_position, GLfloat z_position);
	virtual ~Camera();

	void move(GLfloat delta_front_back, GLfloat delta_left_right);
	void rotate(GLfloat delta_horizontal_angle, GLfloat delta_vertical_angle);

	void update(float time);

private:
	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLfloat r_x;
	GLfloat r_y;
	GLfloat r_z;

	GLfloat horizontal_angle;
	GLfloat vertical_angle;
};

//} /* namespace camera */

#endif /* CAMERA_CAMERA_H_ */
