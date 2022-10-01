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
	GameObject(Model* model3D, glm::vec3 transform);
	virtual void Update(float deltaTime, Shader shader, float, float);
	glm::vec3 transform;
	bool destroy = false;
	~GameObject();
protected:
	uint32_t id = 0;
	Model* model3D;
	glm::mat4 model = glm::mat4(1.0f);


	float timeToDestroy = 3.0f;

	void Draw(Shader shader);

};

#endif