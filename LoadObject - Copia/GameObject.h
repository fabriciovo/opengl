#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Model.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject
{
public:
	GameObject();
	GameObject(std::string model, glm::vec3 position, glm::vec3 scale, float size = 1.0f);
	virtual void Update(float deltaTime, Shader shader);
	glm::mat4 GetTransformMatrix();
	bool Collision(std::vector<GameObject*> other);
	bool destroy = false;
	float size = 1.0f;

	~GameObject();
protected:
	uint32_t id;
	Model* model3D;
	glm::vec3 position;
	glm::vec3 scale;
	float rotaion_angle;
	float timeToDestroy = 3.0f;


};

#endif