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
std::string Perlin::FRAGMENT_FILE = "src/shader/perlin_noise.frag";

Perlin::Perlin(int octaves) {
	this->octaves= octaves;
	this->octaves_location = 0;
	this->shader = 0;
	this->time_location = 0;
	this->program = 0;
}

Perlin::~Perlin() {
	// TODO Auto-generated destructor stub
}

void Perlin::update(float time) {
	shader::ShaderManager::setUniformFloatValue(time_location, time);
}

void Perlin::show() {
	program = shader::ShaderManager::createShader(FRAGMENT_FILE, shader::ShaderType::FRAGMENT);

	octaves_location = shader::ShaderManager::getUniformLocation(program, OCTAVES_UNIFORM);
	time_location = shader::ShaderManager::getUniformLocation(program, TIME_UNIFORM);

	shader::ShaderManager::setUniformIntValue(octaves_location, octaves);
}

}

