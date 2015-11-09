/*
 * ShaderManager.h
 *
 *  Created on: 9 de nov de 2015
 *      Author: cassiano
 */

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#include "../textfile.h"

#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

namespace shader {

enum class ShaderType { VERTEX, FRAGMENT };

class ShaderManager {
public:
	static GLint createShader(std::string, ShaderType) throw(std::string);
	static GLint getUniformLocation(const GLint, const std::string);

	static void setUniformIntValue(const GLint, int);
	static void setUniformFloatValue(const GLint, float);
};

} /* namespace shader */

#endif /* SHADERMANAGER_H_ */
