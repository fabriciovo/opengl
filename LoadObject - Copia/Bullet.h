#ifndef BULLET_H
#define BULLET_H
#include "Model.h"
#include "Camera.h"
#include "GameObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Bullet : public GameObject
{
public:
	Bullet(std::string model, glm::vec3 transform, glm::vec3 scale, glm::vec3 dir);
	void Update(float deltaTime, Shader shader);
	~Bullet();
private:
	float timer = 10.0f;
	float size = 1;
	glm::vec3 dir;
};

#endif