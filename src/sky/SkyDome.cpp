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

	indexes = nullptr;

	step_circle = 4;
	step_height = 3;

	//this->vertex_size = (int) 6 * ((360 / angle_step) + 1);
	//this->vertex = new GLfloat[vertex_size];

	//Total_Points
	this->vertex_size = Total_Points * 6;
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

	makePoints();

	makeIndexes();

	/*
	 for (int i = 0, j = 0; i <= 360; i += angle_step, j += 6) {

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
	 */
	if (DEBUG_POINTS) {
		for (int i = 0; i < vertex_size; i += 3) {
			std::cout << "(x, y, z) => (" << vertex[i] << ", " << vertex[i + 1]
					<< ", " << vertex[i + 2] << ")\n";
		}

		std::cout << "Number of Vertex: " << vertex_size << std::endl;
	}

	update(0);
}

void SkyDome::makeIndexes() {

	std::ofstream file;
	file.open("points.txt");

	indexes = new int[6 * step_circle * step_height];

	for (int i = 1; i <= step_height; ++i) {

		int first_circle_point = (i-1) * step_circle;
		int actual_circle_point = first_circle_point;

		for (int j = 0; j < step_circle; ++j) {
			int position = j*6;

			int last = actual_circle_point + step_circle;

			indexes[position] = actual_circle_point;

			actual_circle_point = (actual_circle_point + 1) % (actual_circle_point + step_circle);

			indexes[position + 1] = actual_circle_point;
			indexes[position + 3] = actual_circle_point;

			//*********************************

			indexes[position + 2] = last;
			indexes[position + 4] = last;

			indexes[position + 5] = last + 1;

			file << "(" << indexes[position] << ", " << indexes[position+1] << ", " << indexes[position+2] << ")\t";
			file << "(" << indexes[position+3] << ", " << indexes[position+4] << ", " << indexes[position+5] << ")\n";
		}
	}
	file.close();

}

void SkyDome::update(float time) {

	// Set values here

	glColor3f(1.0, 1.0, 0.0);
	glPolygonMode( GL_BACK, GL_LINE);

	glBegin(GL_TRIANGLE_STRIP);
	//glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < vertex_size; i += 3) {
		glVertex3f(vertex[i], vertex[i + 1], vertex[i + 2]);
	}
	glEnd();
}

void SkyDome::makePoints() {
	int i;
	float x_angle;
	float y_angle;

	unsigned int mean = (unsigned int) vertex_size * 0.5;

	for (i = 0; i < Total_Points; i++) {
		x_angle = (float) (i & 1) + (i >> Band_Power);

		y_angle = (float) ((i & Band_Mask) >> 1)
				+ ((i >> Band_Power) * (Sections_In_Band));

		x_angle *= (float) Section_Arc; // remember - 180° x rot not 360
		y_angle *= (float) Section_Arc * -2;

		float cos_x_angle = cos(x_angle);
		float cos_y_angle = cos(y_angle);

		float sin_x_angle = sin(x_angle);
		float sin_y_angle = sin(y_angle);

		unsigned int position = i * 3;

		vertex[position] = ray * sin_x_angle * sin_y_angle;
		vertex[position + 1] = ray * cos_x_angle;
		vertex[position + 2] = ray * sin_x_angle * cos_y_angle;

		vertex[position + mean] = -ray * sin_x_angle * sin_y_angle;
		vertex[position + mean + 1] = ray * cos_x_angle;
		vertex[position + mean + 2] = -ray * sin_x_angle * cos_y_angle;
	}
}

} /* namespace sky */
