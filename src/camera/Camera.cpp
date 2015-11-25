/*
 * Camera.cpp
 *
 *  Created on: 18 de nov de 2015
 *      Author: cassiano
 */

#include "Camera.h"
#include <iostream> // TODO remove

Camera::Camera(GLfloat x_position, GLfloat y_position, GLfloat z_position,
		GLfloat horizontal_angle, GLfloat vertical_angle) {

	x = x_position;
	y = y_position;
	z = z_position;

	this->horizontal_angle = horizontal_angle;
	this->vertical_angle = vertical_angle;

	look_vector_x = 0.0f;
	look_vector_y = 0.0f;
	look_vector_z = 0.0f;

	rotate(horizontal_angle, vertical_angle);
}

Camera::~Camera() {
}

void Camera::move(GLfloat delta_front_back, GLfloat delta_left_right) {
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 look_vector(look_vector_x, look_vector_y, look_vector_z);
	glm::vec3 right = glm::cross(up, look_vector);

	x += (right.x * 0.10) * delta_left_right;
	z += (right.z * 0.10) * delta_left_right;

	x += (look_vector_x * 0.10) * delta_front_back;
	z += (look_vector_z * 0.10) * delta_front_back;
}

void Camera::rotate(GLfloat delta_horizontal_angle,
		GLfloat delta_vertical_angle) {
	horizontal_angle += delta_horizontal_angle;
	vertical_angle += delta_vertical_angle;

	GLfloat horizontal_rad = fmod(horizontal_angle, 360.0) * TO_RAD;
	GLfloat vertical_rad = fmod(vertical_angle, 180.0) * TO_RAD;

	look_vector_x = sin(vertical_rad) * cos(horizontal_rad);
	look_vector_y = cos(vertical_rad);
	look_vector_z = sin(vertical_rad) * sin(horizontal_rad);
}

void Camera::update(float time) {
	gluLookAt(x, y, z, look_vector_x + x, look_vector_y + y, look_vector_z + z,
			0.0f, 1.0f, 0.0f);

#if DEBUG_CAMERA
	std::cout << "hangle: " << horizontal_angle << "\n";
	std::cout << "vangle: " << vertical_angle << "\n";
	std::cout << "cam_pos: (" << x << ", " << y << ", " << z << ")\n";
	std::cout << "look_to: (" << look_vector_x << ", " << look_vector_y << ", "
			<< look_vector_z << ")\n\n";
#endif
}
