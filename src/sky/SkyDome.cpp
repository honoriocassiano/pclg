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

	step_circle = 4;
	step_height = 3;

	step_circle_angle = 360.0 / step_circle;
	step_height_angle = 90.0 / step_height;

	//this->vertex_size = (int) 6 * ((360 / angle_step) + 1);
	//this->vertex = new GLfloat[vertex_size];

	//Total_Points
	this->vertex_size = step_circle * step_height * 3;
	this->vertex = new GLfloat[vertex_size];
	this->indexes = new int[6 * step_circle * step_height];
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

		std::cout << "Number of Vertex: " << vertex_size / 3 << std::endl;
	}

	update(0);
}

void SkyDome::makeIndexes() {

//	std::ofstream file;
//	file.open("points.txt");

	for (int i = 1; i <= step_height; ++i) {

		int first_circle_point = (i - 1) * step_circle;
		int actual_circle_point = first_circle_point;

		for (int j = 0; j < step_circle; ++j) {
			int position = j * 6;

			int last = actual_circle_point + step_circle;

			indexes[position] = actual_circle_point;

			actual_circle_point = (actual_circle_point + 1)
					% (actual_circle_point + step_circle);

			indexes[position + 1] = actual_circle_point;
			indexes[position + 3] = actual_circle_point;

			//*********************************

			indexes[position + 2] = last;
			indexes[position + 4] = last;

			indexes[position + 5] = last + 1;

//			file << "(" << indexes[position] << ", " << indexes[position+1] << ", " << indexes[position+2] << ")\t";
//			file << "(" << indexes[position+3] << ", " << indexes[position+4] << ", " << indexes[position+5] << ")\n";
		}
	}
//	file.close();

}

void SkyDome::update(float time) {

	// Set values here

	glColor3f(1.0, 1.0, 0.0);
	//glPolygonMode( GL_BACK, GL_LINE);

	/*
	 glBegin(GL_TRIANGLE_STRIP);
	 //glBegin(GL_QUAD_STRIP);
	 for (int i = 0; i < vertex_size; i += 3) {
	 glVertex3f(vertex[i], vertex[i + 1], vertex[i + 2]);
	 }
	 glEnd();
	 */

	glBindBuffer(GL_ARRAY_BUFFER, vertex_id);	//use this VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_id);	//and index
	glEnableClientState(GL_VERTEX_ARRAY);	//we use vertex and
	//glEnableClientState(GL_COLOR_ARRAY);	//color data
	//the vertex has 3 component (x,y,z),it has the type float, 3 float is the vertex + 3 float is the color/6*sizeof(float), and the first
	//coordinate start at the begginning of the VBO
	//glVertexPointer(3,GL_FLOAT,6*sizeof(float),0);
	glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), 0);
	//same thing
	//glColorPointer(3,GL_FLOAT,6*sizeof(float),(void*)(3*sizeof(float)));
	//glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0);		//draw it

	// SEGUNDO PARÂMETRO: QUANTIDADE DE ELEMENTOS A SEREM DESENHADOS

//	glDrawElements(GL_TRIANGLES, 6 * step_circle * step_height,
//	GL_UNSIGNED_INT, 0);		//draw it

	glDrawElements(GL_TRIANGLES, 12,
		GL_UNSIGNED_INT, 0);		//draw it

	//glDisableClientState(GL_COLOR_ARRAY);	//disable everything
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void SkyDome::makeVBO() {

	GLfloat vertex[] = { 0, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, -1, -1, -1, 0,
			-1, 0, -1, 0, -1, -1, -1, -1, -1 };
	int indexes[] = { 0, 1, 4, 1, 5, 4, 1, 2, 5, 2, 6, 5, 2, 3, 6, 3, 7, 6, 3,
			0, 7, 0, 4, 3, 0, 1, 3, 1, 2, 3, 4, 5, 7, 5, 6, 7 };

	glGenBuffers(1, &vertex_id);	//generate an index for the vertexbuffer
	glGenBuffers(1, &indexes_id);	//and the indices
	glBindBuffer(GL_ARRAY_BUFFER, vertex_id);	//use vbo as ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_id);//use ind as ELEMENT_ARRAY_BUFFER (index-array)
//	glBufferData(GL_ARRAY_BUFFER, vertex_size, vertex, GL_STATIC_DRAW);	//fill up the array with vertex and color-data
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_size * 2, indexes, GL_STATIC_DRAW);	//this one with indicis

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);	//fill up the array with vertex and color-data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes,
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

			GLfloat x = ray * sin(height_angle_rad) * cos(circle_angle_rad);
			GLfloat y = ray * sin(height_angle_rad) * sin(circle_angle_rad);
			GLfloat z = ray * cos(height_angle_rad);

			vertex[counter] = x;
			vertex[counter + 1] = y;
			vertex[counter + 2] = z;

//			std::cout << vertex[counter] << " " << vertex[counter+1] << " " << vertex[counter+2] << std::endl;
//			std::cout << i << std::endl;

			counter += 3;
		}
	}
	/*
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
	 */
}

} /* namespace sky */
