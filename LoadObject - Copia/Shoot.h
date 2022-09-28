#ifndef SHOOT_H
#define SHOOT_H
#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shoot
{
public:
	Shoot(Model * model3D, glm::vec3 transform);
	void Update(float deltaTime, Shader shader);
private:
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 transform;
	Model* model3D;
};

#endif