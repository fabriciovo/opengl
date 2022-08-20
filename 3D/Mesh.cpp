#ifndef OBJ3D_CLASS_H
#define OBJ3D_CLASS_H

#include "Mesh.h"
#include <glm/glm.hpp>
#include<string>
#include<vector>

using namespace std;
using namespace glm;

class Mesh {
    string mtllib;
    vec3 min, max;
    vector<vec3*> vertices;
    // ... 
};

#endif