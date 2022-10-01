#include "Player.h"



Player::Player(std::string model, glm::vec3 position, glm::vec3 scale, Camera * camera, GLFWwindow* window) {
    this->position = camera->Position;
    this->model3D = new Model(model);
    this->model = glm::translate(this->model, this->position); 
    this->model = glm::scale(this->model, scale);
    this->camera = camera;
    this->window = window;
}


void Player::Update(float deltaTime, Shader shader) {
	GameObject::Update(deltaTime, shader);

    this->model = glm::rotate(glm::mat4(1.0f), 3.14f, glm::vec3(1.0));
    this->model = glm::translate(this->model, camera->Position * camera->Orientation);


}

Player::~Player()
{

}
