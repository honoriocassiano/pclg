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

#define DEBUG_SHADER 0

namespace shader {

enum class ShaderType { VERTEX, FRAGMENT };

class ShaderManager {
public:
	static GLint createShader(std::string, ShaderType, GLint = 0) throw(std::string);
	static GLint getUniformLocation(const GLint, const std::string);

	static void setUniformIntValue(const GLint, int);
	static void setUniformFloatValue(const GLint, float);

	static void setProgramState(const GLint, bool);

private:
#if DEBUG_SHADER
	static void printShaderInfoLog(std::string name, GLuint object);
	static void printProgramInfoLog(GLuint obj);
#endif

};

} /* namespace shader */

#endif /* SHADERMANAGER_H_ */
