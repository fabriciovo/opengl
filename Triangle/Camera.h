#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

using namespace glm;

class Camera {
public:
	vec3 Position;
	vec3 Orientaion = vec3(0.0f, 0.0f, -1.0f);
	vec3 Up = vec3(0.0f, 1.0f, 0.0f);
};




#endif