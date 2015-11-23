/*
 * Camera.cpp
 *
 *  Created on: 18 de nov de 2015
 *      Author: cassiano
 */

#include "Camera.h"
#include <iostream> // TODO remove

Camera::Camera(GLfloat x_position, GLfloat y_position, GLfloat z_position,
		GLfloat horizontal_angle, GLfloat vertical_angle) :
		x(x_position), y(y_position), z(z_position), horizontal_angle(horizontal_angle),
		vertical_angle(vertical_angle), look_vector_x(0.0), look_vector_y(0.0), look_vector_z(0.0) {}

Camera::~Camera() {}

void Camera::move(GLfloat delta_up_down, GLfloat delta_left_right) {}

void Camera::rotate(GLfloat delta_horizontal_angle, GLfloat delta_vertical_angle) {
	horizontal_angle += delta_horizontal_angle;
	vertical_angle += delta_vertical_angle;

	GLfloat horizontal_rad = fmod(horizontal_angle, 360.0) * TO_RAD;
	GLfloat vertical_rad = fmod(vertical_angle, 180.0) * TO_RAD;

	look_vector_x = sin(vertical_rad) * cos(horizontal_rad);
	look_vector_y = cos(vertical_rad);
	look_vector_z = sin(vertical_rad) * sin(horizontal_rad);

	std::cout << "hangle: " << horizontal_angle << "\n";
	std::cout << "vangle: " << vertical_angle << "\n";
	std::cout << "cam_pos: (" << x << ", " << y << ", " << z << ")\n";
	std::cout << "look_to: (" << look_vector_x + x << ", " << look_vector_y + y << ", " << look_vector_z + z << ")\n\n";
}

void Camera::update(float time) {
	gluLookAt(x, y, z, look_vector_x + x, look_vector_y + y, look_vector_z + z, 0.0f, 1.0f, 0.0f);
}
