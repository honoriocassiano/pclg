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
	this->radius = ray;
	this->angle_step = angle_step;

	step_circle = 10;
	step_height = 5;

	step_circle_angle = 360.0 / step_circle;
	step_height_angle = 90.0 / step_height;

	//this->vertex_size = (int) 6 * ((360 / angle_step) + 1);
	//this->vertex = new GLfloat[vertex_size];

	//Total_Points
	this->vertex_size = step_circle * step_height * 3;

	this->indexes_size = 6 * step_circle * (step_height - 1);

	this->vertex = new GLfloat[vertex_size];
	this->indexes = new int[indexes_size];

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
	makeVBO();

	std::cout << glewGetErrorString(glGetError()) << std::endl;

	if (DEBUG_POINTS) {
		for (int i = 0; i < vertex_size; i += 3) {
			std::cout << "(x, y, z) => (" << vertex[i] << ", " << vertex[i + 1]
					<< ", " << vertex[i + 2] << ")\n";
		}

		std::cout << "Number of Vertex: " << vertex_size / 3 << std::endl;

	}

	if (DEBUG_INDEX) {

		for (int i = 0; i < indexes_size; i += 3) {
			std::cout << "Triangle => (" << indexes[i] << ", " << indexes[i + 1]
					<< ", " << indexes[i + 2] << ")\n";
		}

		std::cout << "Number of Index: " << indexes_size << std::endl;
	}

	update(0);
}

void SkyDome::makeIndexes() {

//	std::ofstream file;
//	file.open("points.txt");

	int position = 0;

	for (int i = 1; i <= step_height; ++i) {

		int first_circle_point = (i - 1) * step_circle;
		int actual_circle_point = first_circle_point;

		for (int j = 0; j < step_circle; ++j) {

			int last = actual_circle_point + step_circle;

			indexes[position] = actual_circle_point;

			//std::cout << actual_circle_point << std::endl;

			actual_circle_point = (actual_circle_point + 1)
					% (actual_circle_point + step_circle);

			indexes[position + 1] = actual_circle_point;
			indexes[position + 3] = actual_circle_point;

			//*********************************

			indexes[position + 2] = last;
			indexes[position + 4] = last;

			indexes[position + 5] = last + 1;

			position += 6;
		}
	}
}

void SkyDome::update(float time) {

	// Set values here

	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode( GL_FRONT, GL_LINE);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_id);	//use this VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_id);	//and index
	glEnableClientState(GL_VERTEX_ARRAY);	//we use vertex and
	//the vertex has 3 component (x,y,z),it has the type float, 3 float is the vertex + 3 float is the color/6*sizeof(float), and the first
	//coordinate start at the begginning of the VBO
	glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), 0);
	//same thing

	// SEGUNDO PARÂMETRO: QUANTIDADE DE ELEMENTOS A SEREM DESENHADOS

	glDrawElements(GL_TRIANGLES, indexes_size,
	GL_UNSIGNED_INT, (void *) 0);		//draw it

//	glDrawArrays(GL_TRIANGLE_STRIP, 0, indexes_size);

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SkyDome::makeVBO() {

	//GLfloat vertex[] = {0,2,0,-2,-2,0,2,-2,0};
	//int indexes[] = {0,1,2};	//index array
	glGenBuffers(1, &vertex_id);	//generate an index for the vertexbuffer
	glGenBuffers(1, &indexes_id);	//and the indices
	glBindBuffer(GL_ARRAY_BUFFER, vertex_id);	//use vbo as ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_id);//use ind as ELEMENT_ARRAY_BUFFER (index-array)
//	glBufferData(GL_ARRAY_BUFFER, vertex_size, vertex, GL_STATIC_DRAW);	//fill up the array with vertex and color-data
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_size * 2, indexes, GL_STATIC_DRAW);	//this one with indicis

//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);	//fill up the array with vertex and color-data
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes,
//			GL_STATIC_DRAW);	//this one with indicis

	glBufferData(GL_ARRAY_BUFFER, vertex_size * sizeof(GLfloat), vertex,
	GL_STATIC_DRAW);	//fill up the array with vertex and color-data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes_size * sizeof(int), indexes,
	GL_STATIC_DRAW);	//this one with indicis
}

void SkyDome::makePoints() {

	int counter = 0;

	float x_angle;
	float y_angle;

	unsigned int mean = (unsigned int) vertex_size * 0.5;

	for (int i = step_height; i > 0; --i) {

		GLfloat height_angle = 90 - i * step_height_angle;

		GLfloat height_angle_rad = height_angle * to_rad;

		for (int j = 0; j < step_circle; ++j) {
			GLfloat circle_angle = j * step_circle_angle;

			GLfloat circle_angle_rad = circle_angle * to_rad;

			GLfloat x = radius * sin(height_angle_rad) * cos(circle_angle_rad);
			GLfloat y = radius * sin(height_angle_rad) * sin(circle_angle_rad);
			GLfloat z = radius * cos(height_angle_rad);

			vertex[counter] = x;
			vertex[counter + 1] = y;
			vertex[counter + 2] = z;

//			std::cout << vertex[counter] << " " << vertex[counter+1] << " " << vertex[counter+2] << std::endl;
//			std::cout << i << std::endl;

			counter += 3;
		}
	}
}

} /* namespace sky */
