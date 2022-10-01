#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::GameObject(std::string model, glm::vec3 position, glm::vec3 scale)
{
    this->id = reinterpret_cast<uint32_t>(this);
    this->model3D = new Model(model);
    this->position = position;
    this->model = glm::translate(this->model, this->position); // translate it down so it's at the center of the scene
    this->model = glm::scale(this->model, scale);	// it's a bit too big for our scene, so scale it down
}

void GameObject::Update(float deltaTime, Shader shader)
{
    shader.setMat4("model", this->model);
    this->model3D->Draw(shader);
}

GameObject::~GameObject()
{
    std::cout << "foi" << std::endl;

}
