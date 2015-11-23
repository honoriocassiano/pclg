/*
 * Camera.cpp
 *
 *  Created on: 18 de nov de 2015
 *      Author: cassiano
 */

#include "Camera.h"
#include <iostream> // TODO remove

//namespace camera {

Camera::Camera(GLfloat x_position, GLfloat y_position, GLfloat z_position,
		GLfloat horizontal_angle, GLfloat vertical_angle) {
	this->x = x_position;
	this->y = y_position;
	this->z = z_position;

	this->look_to_x = 0.0;
	this->look_to_y = 0.0;
	this->look_to_z = 0.0;

	this->horizontal_angle = horizontal_angle;
	this->vertical_angle = vertical_angle;
}

Camera::~Camera() {
}

void Camera::move(GLfloat delta_up_down, GLfloat delta_left_right) {

}

void Camera::rotate(GLfloat delta_horizontal_angle, GLfloat delta_vertical_angle) {
	horizontal_angle += delta_horizontal_angle;
	vertical_angle += delta_vertical_angle;

	GLfloat horizontal_rad = fmod(horizontal_angle * TO_RAD, 360.0);
	GLfloat vertical_rad = fmod(vertical_angle * TO_RAD, 180.0);

	look_to_x = (sin(vertical_rad) * cos(horizontal_rad) * 5) + x;
	look_to_y = (cos(vertical_rad) * 5) + y;
	look_to_z = (sin(vertical_rad) * sin(horizontal_rad) * 5) + z;

	std::cout << "hangle: " << horizontal_angle << "\n";
	std::cout << "vangle: " << vertical_angle << "\n";
	std::cout << "cam_pos: (" << x << ", " << y << ", " << z << ")\n";
	std::cout << "look_to: (" << look_to_x << ", " << look_to_y << ", " << look_to_z << ")\n\n";
}

void Camera::update(float time) {
	gluLookAt(x, y, z, look_to_x, look_to_y, look_to_z, 0.0f, 1.0f, 0.0f);
}

//} /* namespace camera */
