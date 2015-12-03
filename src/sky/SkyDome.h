/*
 * SkyDome.h
 *
 *  Created on: 10 de nov de 2015
 *      Author: cassiano
 */

#include <math.h>
#include <fstream>

#include "../noise/Perlin.h"
#include "Surface.h"

#ifndef SKYDOME_H_
#define SKYDOME_H_

namespace sky {

class SkyDome: public Surface {
public:
	SkyDome(GLfloat radius, int horizontal_sections, int vertical_sections);
	virtual ~SkyDome();

	virtual void show();
	virtual void update(float);

private:
	static GLfloat to_rad;

	GLfloat radius;
	int v_sections;
	int h_sections;

	int vertex_size;
	int index_size;

	GLfloat step_circle_angle;
	GLfloat step_height_angle;

	GLuint vertex_id;
	GLuint vertex_index_id;

	GLfloat * vertex;
	GLuint * vertex_index;

	void makeVBO();
	void makePoints();
	void makeIndexes();
};

} /* namespace shader */

#endif /* SKYDOME_H_ */

