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

#define DEBUG_POINTS 0
#define DEBUG_INDEX 0

#define Band_Power  4  // 2^Band_Power = Total Points in a band.
#define Band_Points 16 // 16 = 2^Band_Power
#define Band_Mask (Band_Points-2)

const int Sections_In_Band = (Band_Points / 2) - 1;

const float Section_Arc = M_PI / (Sections_In_Band * 2.0);
const float R = 1; // radius of 10

#define Total_Points (Sections_In_Band*Band_Points)

namespace sky {

class SkyDome: public Surface {
public:
	SkyDome(GLfloat, int);
	virtual ~SkyDome();

	virtual void show();
	virtual void update(float);
	virtual void makePoints();
	virtual void makeIndexes();


private:
	GLfloat radius;
	int vertex_size;
	int indexes_size;
	int angle_step;
	GLuint triangleVBO;
	GLfloat * vertex;
	static GLfloat to_rad;

	int step_height;
	int step_circle;

	GLfloat step_circle_angle;
	GLfloat step_height_angle;

	GLuint vertex_id;
	GLuint indexes_id;

	int * indexes;

	void makeVBO();
};

} /* namespace shader */

#endif /* SKYDOME_H_ */

