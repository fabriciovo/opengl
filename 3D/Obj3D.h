#ifndef OBJ3D_CLASS_H
#define OBJ3D_CLASS_H

#include "Mesh.h"
#include <glm/glm.hpp>

using namespace glm;

class Obj3D {
	Mesh* mesh;
	mat4 transform;
	int status;
	bool eliminavel;
	vec3 direcao;
};

#endif