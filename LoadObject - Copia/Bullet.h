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
	Bullet(Model* model3D, glm::vec3 transform);
	void Update(float deltaTime, Shader shader,  float, float);
	~Bullet();
private:
	float timer = 10.0f;
};

#endif