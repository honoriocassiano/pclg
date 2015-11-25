/*
 * ShaderManager.cpp
 *
 *  Created on: 9 de nov de 2015
 *      Author: cassiano
 */

#include "ShaderManager.h"

namespace shader {

GLint ShaderManager::createShader(std::string file_location, ShaderType type,
		GLint program_to_attach) throw (std::string) {

	GLint shader, program;

	if (type == ShaderType::FRAGMENT) {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	} else if (type == ShaderType::VERTEX) {
		shader = glCreateShader(GL_VERTEX_SHADER);
	}

#if DEBUG_SHADER
	ShaderManager::printShaderInfoLog(file_location, shader);
#endif

	char *shader_text = textFileRead(file_location.c_str());

	if (shader_text == NULL) {
		//std::cout << "Shader file not found!\n";
		throw "Shader file \"" + file_location + "\" not found!\n";
	} else {
		std::cout << "Shader created from file \"" << file_location << "\"\n";
	}

	const char * ff = shader_text;

	glShaderSource(shader, 1, &ff, NULL);

	delete shader_text;

	glCompileShader(shader);

	if (program_to_attach == 0) {
		// std::cout << "Creating new program\n";
		program = glCreateProgram();
	} else {
		// std::cout << "Reusing program\n";
		program = program_to_attach;
	}

	glAttachShader(program, shader);
	glLinkProgram(program);

#if DEBUG_SHADER
	printProgramInfoLog(program);
#endif

	return program;
}

GLint ShaderManager::getUniformLocation(const GLint program,
		const std::string name) {
	return glGetUniformLocation(program, name.c_str());
}

void ShaderManager::setUniformIntValue(const GLint location, int value) {
	glUniform1iARB(location, value);
}

void ShaderManager::setUniformFloatValue(const GLint location, float value) {
	glUniform1fARB(location, value);
}

void ShaderManager::setProgramState(const GLint program, bool state) {
	if (state) {
		glUseProgram(program);
	} else {
		glUseProgram(0);
	}
}

#if DEBUG_SHADER

void ShaderManager::printShaderInfoLog(std::string name, GLuint object) {
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(object, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0) {
		infoLog = (char *) malloc(infologLength);
		glGetShaderInfoLog(object, infologLength, &charsWritten, infoLog);
		std::cout << "Shader " << name << " log:\n\t" << infoLog;

		free(infoLog);
	}
}

void ShaderManager::printProgramInfoLog(GLuint obj) {
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0) {
		infoLog = (char *) malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		std::cout << "Program log: \n\t" << infoLog;

		free(infoLog);
	}
}
#endif

} /* namespace shader */
