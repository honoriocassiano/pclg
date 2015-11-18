/*
 * Camera.cpp
 *
 *  Created on: 18 de nov de 2015
 *      Author: cassiano
 */

#include "Camera.h"

//namespace camera {

Camera::Camera(GLfloat x_position, GLfloat y_position, GLfloat z_position) {
	this->x = x_position;
	this->y = y_position;
	this->z = z_position;

	this->r_x = 0.0;
	this->r_y = 0.0;
	this->r_z = 0.0;

	horizontal_angle = 0.0;
	vertical_angle = 0.0;
}

Camera::~Camera() {
}

void Camera::move(GLfloat delta_front_back, GLfloat delta_left_right) {
	/*
	x = new_x;
	y = new_y;
	z = new_z;
	*/

	x += delta_front_back * sin(horizontal_angle);
	z += delta_front_back * (-cos(horizontal_angle));
}

void Camera::rotate(GLfloat delta_horizontal_angle, GLfloat delta_vertical_angle) {
	/*
	r_x = new_x;
	r_y = new_y;
	r_z = new_z;
	*/
}

void Camera::update(float time) {
	gluLookAt(x, y, z, r_x, r_y, r_z, 0.0f, 1.0f, 0.0f);
}

//} /* namespace camera */
