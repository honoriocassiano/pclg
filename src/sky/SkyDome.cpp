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

SkyDome::SkyDome(GLfloat radius, int horizontal_sections,
		int vertical_sections) {
	this->radius = radius;

	this->h_sections = horizontal_sections;
	this->v_sections = vertical_sections;

	step_circle_angle = 360.0 / h_sections;
	step_height_angle = 90.0 / v_sections;

	//Size of vertex and index vectors
	this->vertex_size = h_sections * v_sections * 3;
	this->index_size = 6 * h_sections * (v_sections - 1);

	this->vertex = new GLfloat[vertex_size];
	this->vertex_index = new GLuint[index_size];

	vertex_id = 0;
	vertex_index_id = 0;
}

SkyDome::~SkyDome() {

}

void SkyDome::show() {

	std::cout << "Drawing SkyDome\n";

	makePoints();
	makeIndexes();
	makeVBO();

#if DEBUG_GLEW
	std::cout << glewGetErrorString(glGetError()) << std::endl;
#endif

#if DEBUG_POINTS
	for (int i = 0; i < vertex_size; i += 3) {
		std::cout << "(x, y, z) => (" << vertex[i] << ", " << vertex[i + 1]
		<< ", " << vertex[i + 2] << ")\n";
	}

	std::cout << "Number of Vertex: " << vertex_size / 3 << std::endl;
#endif

#if DEBUG_INDEX

	for (int i = 0; i < index_size; i += 3) {
		std::cout << "Triangle => (" << vertex_index[i] << ", "
		<< vertex_index[i + 1] << ", " << vertex_index[i + 2]
		<< ")\n";
	}

	std::cout << "Number of Index: " << index_size << std::endl;

#endif

	update(0);
}

void SkyDome::makeIndexes() {

	int position = 0;

	for (int i = 1; i <= v_sections; ++i) {

		int first_circle_point = (i - 1) * h_sections;
		int actual_circle_point = first_circle_point;

		for (int j = 0; j < h_sections; ++j) {

			int last = actual_circle_point + h_sections;

			vertex_index[position] = actual_circle_point;

			actual_circle_point = (actual_circle_point + 1)
					% (actual_circle_point + h_sections);

			vertex_index[position + 1] = actual_circle_point;
			vertex_index[position + 3] = last;

			vertex_index[position + 2] = last;
			vertex_index[position + 4] = actual_circle_point;

			vertex_index[position + 5] = last + 1;

			position += 6;
		}
	}
}

void SkyDome::update(float time) {

	glPolygonMode( GL_BACK, GL_FILL);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_index_id);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), 0);

	glDrawElements(GL_TRIANGLES, index_size - 1,
	GL_UNSIGNED_INT, (void *) 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SkyDome::makeVBO() {

	glGenBuffers(1, &vertex_id);
	glGenBuffers(1, &vertex_index_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_index_id);

	glBufferData(GL_ARRAY_BUFFER, vertex_size * sizeof(GLfloat), vertex,
	GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size * sizeof(int),
			vertex_index,
			GL_STATIC_DRAW);

}

void SkyDome::makePoints() {

	int counter = 0;

	for (int i = v_sections; i > 0; --i) {

		GLfloat height_angle = 90 - i * step_height_angle;

		GLfloat height_angle_rad = height_angle * to_rad;

		for (int j = 0; j < h_sections; ++j) {
			GLfloat circle_angle = j * step_circle_angle;

			GLfloat circle_angle_rad = circle_angle * to_rad;

			GLfloat x = radius * sin(height_angle_rad) * cos(circle_angle_rad);
			GLfloat y = radius * sin(height_angle_rad) * sin(circle_angle_rad);
			GLfloat z = radius * cos(height_angle_rad);

			vertex[counter] = x;
			vertex[counter + 1] = y;
			vertex[counter + 2] = z;

			counter += 3;
		}
	}
}

} /* namespace sky */
