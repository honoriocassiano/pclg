/*
 * SkyDome.h
 *
 *  Created on: 10 de nov de 2015
 *      Author: cassiano
 */

#include <math.h>

#include "../noise/Perlin.h"
#include "Surface.h"

#ifndef SKYDOME_H_
#define SKYDOME_H_

namespace sky {

class SkyDome : public Surface {
public:
	SkyDome(GLfloat, int);
	virtual ~SkyDome();

	virtual void show();
	virtual void update(float);

private:
	GLfloat ray;
	int vertex_size;
	int angle_step;
	GLuint triangleVBO;
	GLfloat * vertex;
	static GLfloat to_rad;
};

} /* namespace shader */

#endif /* SKYDOME_H_ */
