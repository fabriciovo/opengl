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
	Bullet(std::string model, glm::vec3 transform, glm::vec3 scale);
	void Update(float deltaTime, Shader shader,  float, float);
	~Bullet();
private:
	float timer = 3.0f;
};

#endif