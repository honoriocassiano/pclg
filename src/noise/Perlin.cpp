/*
 * Perlin.cpp
 *
 *  Created on: 9 de nov de 2015
 *      Author: cassiano
 */

#include "Perlin.h"

namespace noise {

std::string Perlin::TIME_UNIFORM = "time";
std::string Perlin::HORIZON_UNIFORM = "horizon";
std::string Perlin::OCTAVES_UNIFORM = "octaves";
std::string Perlin::CUTOFF_UNIFORM = "cutoff";
std::string Perlin::SCALE_UNIFORM = "scale";
std::string Perlin::VERTEX_FILE = "src/shader/perlin_noise.vert";
std::string Perlin::FRAGMENT_FILE = "src/shader/perlin_noise.frag";

Perlin::Perlin(int octaves, GLfloat scale, GLfloat cutoff, GLfloat horizon) {
	this->octaves = octaves;
	this->scale = scale;
	this->cutoff = cutoff;
	this->horizon = horizon;

	// Uniform Locations
	this->octaves_location = 0;
	this->time_location = 0;
	this->cutoff_location = 0;
	this->scale_location = 0;
	this->horizon_location = 0;

	this->program = 0;

	this->_is_enabled = false;
}

Perlin::~Perlin() {
	glDeleteProgram(program);
}

void Perlin::update(float time, bool update_surfaces) {

	shader::ShaderManager::setUniformIntValue(octaves_location, octaves);
	shader::ShaderManager::setUniformFloatValue(time_location, time);
	shader::ShaderManager::setUniformFloatValue(cutoff_location, cutoff);
	shader::ShaderManager::setUniformFloatValue(scale_location, scale);
	shader::ShaderManager::setUniformFloatValue(horizon_location, horizon);

	if (update_surfaces) {
		for (uint i = 0; i < surfaces.size(); ++i) {
			surfaces[i]->update(time);
		}
	}
}

void Perlin::disable() {
	_is_enabled = false;
	shader::ShaderManager::setProgramState(program, _is_enabled);
}

void Perlin::enable() {
	_is_enabled = true;
	shader::ShaderManager::setProgramState(program, _is_enabled);
}

bool Perlin::is_enabled() {
	return _is_enabled;
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
	horizon_location = shader::ShaderManager::getUniformLocation(program,
			HORIZON_UNIFORM);

	shader::ShaderManager::setUniformIntValue(octaves_location, octaves);
	shader::ShaderManager::setUniformFloatValue(horizon_location, horizon);

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

