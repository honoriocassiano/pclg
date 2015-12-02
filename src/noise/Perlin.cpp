/*
 * Perlin.cpp
 *
 *  Created on: 9 de nov de 2015
 *      Author: cassiano
 */

#include "Perlin.h"

namespace noise {

std::string Perlin::TIME_UNIFORM = "time";
std::string Perlin::OCTAVES_UNIFORM = "octaves";
std::string Perlin::CUTOFF_UNIFORM = "cutoff";
std::string Perlin::SCALE_UNIFORM = "scale";
std::string Perlin::VERTEX_FILE = "src/shader/perlin_noise.vert";
std::string Perlin::FRAGMENT_FILE = "src/shader/perlin_noise.frag";

Perlin::Perlin(int octaves, GLfloat scale, GLfloat cutoff) {
	this->octaves = octaves;
	this->scale = scale;
	this->cutoff = cutoff;

	// Uniform Locations
	this->octaves_location = 0;
	this->time_location = 0;
	this->cutoff_location = 0;
	this->scale_location = 0;

	this->program = 0;
}

Perlin::~Perlin() {
	glDeleteProgram(program);
}

void Perlin::update(float time, bool update_surfaces) {

	shader::ShaderManager::setProgramState(program, true);

	shader::ShaderManager::setUniformIntValue(octaves_location, octaves);
	shader::ShaderManager::setUniformFloatValue(time_location, time);
	shader::ShaderManager::setUniformFloatValue(cutoff_location, cutoff);
	shader::ShaderManager::setUniformFloatValue(scale_location, scale);

	if (update_surfaces) {
		for (uint i = 0; i < surfaces.size(); ++i) {
			surfaces[i]->update(time);
		}
	}

	shader::ShaderManager::setProgramState(program, false);
}

void Perlin::show(bool show_surfaces) {
	program = shader::ShaderManager::createShader(FRAGMENT_FILE,
			shader::ShaderType::FRAGMENT);

	shader::ShaderManager::createShader(VERTEX_FILE, shader::ShaderType::VERTEX,
			program);

	octaves_location = shader::ShaderManager::getUniformLocation(program,
			OCTAVES_UNIFORM);
	time_location = shader::ShaderManager::getUniformLocation(program,
			TIME_UNIFORM);
	cutoff_location = shader::ShaderManager::getUniformLocation(program,
			CUTOFF_UNIFORM);
	scale_location = shader::ShaderManager::getUniformLocation(program,
			SCALE_UNIFORM);

	shader::ShaderManager::setUniformIntValue(octaves_location, octaves);

	shader::ShaderManager::setProgramState(program, true);

	if (show_surfaces) {
		for (uint i = 0; i < surfaces.size(); ++i) {
			surfaces[i]->show();
		}
	}

	shader::ShaderManager::setProgramState(program, false);
}

void Perlin::apply_to(sky::Surface * surface) {
	surfaces.push_back(surface);
}

GLfloat Perlin::getCutoff() {
	return cutoff;
}

void Perlin::setCutoff(GLfloat cutoff) {
	this->cutoff = cutoff;
}

}

