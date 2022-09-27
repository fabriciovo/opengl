#ifndef SHOOT_CLASS_H
#define SHOOT_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.h"


class Shoot
{
public:
	Shoot(Model model,Shader shader, glm::vec3 transform);

	void Update();
private:
	glm::vec3 transform;
	glm::vec3 scale;
	glm::mat4 modelMat4;
	Model model;
	Shader shader;
};

#endif