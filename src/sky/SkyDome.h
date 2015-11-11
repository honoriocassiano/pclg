/*
 * SkyDome.h
 *
 *  Created on: 10 de nov de 2015
 *      Author: cassiano
 */

#include "../noise/Perlin.h"
#include "Surface.h"

#ifndef SKYDOME_H_
#define SKYDOME_H_

namespace sky {

class SkyDome : public Surface {
public:
	SkyDome(GLfloat);
	virtual ~SkyDome();

	virtual void show();
	virtual void update(float);

private:
	GLfloat ray;

//	GLint program;
//	GLint octaves;
//	GLint time_l;
};

} /* namespace shader */

#endif /* SKYDOME_H_ */
