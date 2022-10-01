#include "Player.h"



Player::Player(std::string model, glm::vec3 position, glm::vec3 scale, Camera * camera, GLFWwindow* window) :GameObject(model, position, scale) {
    this->camera = camera;
    this->window = window;
}


void Player::Update(float deltaTime, Shader shader) {
	GameObject::Update(deltaTime, shader);

    this->model = glm::translate(this->model, camera->Position );


}

Player::~Player()
{

}
