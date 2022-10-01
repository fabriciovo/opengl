#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::GameObject(std::string model, glm::vec3 position, glm::vec3 scale)
{
	this->id = reinterpret_cast<uint32_t>(this);
    this->model3D = new Model(model);
    this->position = position;
    this->scale = scale;
}

void GameObject::Update(float deltaTime, Shader shader)
{
    shader.setMat4("model", this->GetTransformMatrix());
    this->model3D->Draw(shader);
}

glm::mat4 GameObject::GetTransformMatrix()
{
	glm::mat4 tarnslation = glm::translate(glm::mat4(1.0f), glm::vec3(this->position));
	glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f), this->rotaion_angle, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scal = glm::scale(glm::mat4(1.0f), glm::vec3(this->scale));

	return tarnslation * scal * Rotation;

}

bool GameObject::Collision(GameObject* other)
{
	if(this->id != other->id){
		if (
			position.x < other->position.x + other->scale.x &&
			position.x + scale.x > other->position.x &&

			position.y < other->position.y + other->scale.y &&
			position.y + scale.y > other->position.y &&
		
			position.z < other->position.z + other->scale.z &&
			position.z + scale.z > other->position.z
			)
		{
			return true;
		}
	}

	return  false;
}

GameObject::~GameObject()
{

}
