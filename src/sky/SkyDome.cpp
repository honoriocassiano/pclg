/*
 * SkyDome.cpp
 *
 *  Created on: 10 de nov de 2015
 *      Author: cassiano
 */

#include "SkyDome.h"

namespace sky {

SkyDome::SkyDome(GLfloat ray) {
	this->ray = ray;
}

SkyDome::~SkyDome() {
	// TODO Auto-generated destructor stub
}

void SkyDome::show() {
	update(0);
}
void SkyDome::update(float time) {

	// Set values here

	// Draw SkyDome

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.1, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(0.5, 1.0, 0.0);
	glEnd();

	// shader::ShaderManager::setProgramState(program, false);
}

} /* namespace sky */
