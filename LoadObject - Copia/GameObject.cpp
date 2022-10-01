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
    this->model = glm::translate(this->model, this->position);
    this->model = glm::scale(this->model, this->scale);
}

void GameObject::Update(float deltaTime, Shader shader)
{
    shader.setMat4("model", this->model);
    this->model3D->Draw(shader);
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
