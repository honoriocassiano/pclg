/*
 * ShaderManager.cpp
 *
 *  Created on: 9 de nov de 2015
 *      Author: cassiano
 */

#include "ShaderManager.h"

namespace shader {

GLint ShaderManager::createShader(std::string file_location, ShaderType type) throw(std::string) {

	GLint shader, program;

	if (type == ShaderType::FRAGMENT) {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	} else if (type == ShaderType::VERTEX) {
		shader = glCreateShader(GL_VERTEX_SHADER);
	}

	char *shader_text = textFileRead(file_location.c_str());

	if (shader_text == NULL) {
		//std::cout << "Shader file not found!\n";
		throw "Shader file \"" + file_location + "\" not found!\n";
	}

	const char * ff = shader_text;

	glShaderSource(shader, 1, &ff, NULL);

	delete shader_text;

	glCompileShader(shader);

	program = glCreateProgram();

	glAttachShader(program, shader);
	glLinkProgram(program);

	glUseProgram(program);

	return program;
}

GLint ShaderManager::getUniformLocation(const GLint program, const std::string name) {
	return glGetUniformLocation(program, name.c_str());
}

void ShaderManager::setUniformIntValue(const GLint location, int value) {
	glUniform1iARB(location, value);
}

void ShaderManager::setUniformFloatValue(const GLint location, float value) {
	glUniform1fARB(location, value);
}

} /* namespace shader */
