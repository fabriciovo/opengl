#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::GameObject(std::string model, glm::vec3 position, glm::vec3 scale, float size)
{
	this->id = reinterpret_cast<uint32_t>(this);
    this->model3D = new Model(model);
    this->position = position;
    this->scale = scale;
	this->size = size;
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
	glm::mat4 scal = glm::scale(glm::mat4(1.0f), glm::vec3(this->scale.x, this->scale.y, this->scale.z ));

	return tarnslation * scal * Rotation;

}

bool GameObject::Collision(std::vector<GameObject*> others)
{
	for(int i = 0; i< others.size(); i++){
		if (this->id != others[i]->id) {
			if (
				this->position.x < others[i]->position.x + others[i]->scale.x * others[i]->size &&
				this->position.x + this->scale.x * this->size > others[i]->position.x &&

				this->position.y < others[i]->position.y + others[i]->scale.y * others[i]->size &&
				this->position.y + this->scale.y * this->size > others[i]->position.y &&

				this->position.z < others[i]->position.z + others[i]->scale.z * others[i]->size &&
				this->position.z + this->scale.z * this->size > others[i]->position.z
				)
			{

				return true;
			}
		}
	}

	return  false;
}

GameObject::~GameObject()
{

}
