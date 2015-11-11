/*
 * SkyDome.cpp
 *
 *  Created on: 10 de nov de 2015
 *      Author: cassiano
 */

#include "SkyDome.h"

#include <GL/glew.h>
#include <iostream>

namespace sky {

GLfloat SkyDome::to_rad = M_PI / 180.0;

SkyDome::SkyDome(GLfloat ray, int angle_step) {
	this->ray = ray;
	this->angle_step = angle_step;
	this->vertex_size = (int) 6 * ((360 / angle_step) + 1);
	this->vertex = new GLfloat[vertex_size];
}

SkyDome::~SkyDome() {
	// TODO Auto-generated destructor stub
}

void SkyDome::show() {

	// TODO Usar VBO parar armazenar e desenhar os vértices

	std::cout << "Drawing SkyDome\n";

	GLfloat v_x = 0.0;
	GLfloat v_y = 0.0;
	GLfloat v_z = 0.0;

	for (int i = 0, j = 0; i <= 360; i += angle_step, j+= 6) {

		float degInRad = i * to_rad;

		v_x = cos(degInRad) * 1.0;
		v_y = sin(degInRad) * 1.0;

		this->vertex[j] = v_x;
		this->vertex[j + 1] = v_y;
		this->vertex[j + 2] = 0.0;

		this->vertex[j + 3] = v_x;
		this->vertex[j + 4] = v_y;
		this->vertex[j + 5] = 1.0;

		//std::cout << "(x, y) => (" << v_x << ", " << v_y << ")\n";
	}

	for (int i = 0; i < vertex_size; i += 3) {
		std::cout << "(x, y, z) => (" << vertex[i] << ", " << vertex[i+1] << ", " << vertex[i+2] << ")\n";
	}

	update(0);
}
void SkyDome::update(float time) {

	// Set values here

	// Draw SkyDome

	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_TRIANGLE_STRIP);
		for(int i = 0; i < vertex_size; i += 3) {
			glVertex3f(vertex[i], vertex[i+1], vertex[i+2]);
		}
	glEnd();
}

} /* namespace sky */
