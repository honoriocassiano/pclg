/*
 * Perlin.h
 *
 *  Created on: 9 de nov de 2015
 *      Author: cassiano
 */

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

#include "../shader/ShaderManager.h"
#include "../sky/Surface.h"

#ifndef PERLIN_H_
#define PERLIN_H_

namespace noise {

class Perlin {
public:
	Perlin(int octaves, GLfloat scale, GLfloat cutoff, GLfloat horizon);
	virtual ~Perlin();

	GLfloat getCutoff();
	void setCutoff(GLfloat cutoff);
	void update(float, bool = true);
	void apply_to(sky::Surface *);
	void show(bool = true);
	void disable();
	void enable();
	bool is_enabled();

private:

	bool _is_enabled;

	std::vector<sky::Surface *> surfaces;
	int octaves;
	GLfloat cutoff;
	GLfloat scale;
	GLfloat horizon;

	GLint time_location;
	GLint octaves_location;
	GLint cutoff_location;
	GLint scale_location;
	GLint horizon_location;

	GLuint program;

	static std::string TIME_UNIFORM;
	static std::string OCTAVES_UNIFORM;
	static std::string CUTOFF_UNIFORM;
	static std::string SCALE_UNIFORM;
	static std::string HORIZON_UNIFORM;
	static std::string FRAGMENT_FILE;
	static std::string VERTEX_FILE;
};

} /* namespace words */

#endif /* PERLIN_H_ */
