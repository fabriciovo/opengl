#include "Bullet.h"


Bullet::Bullet(std::string model, glm::vec3 position, glm::vec3 scale) {
    this->position = position;
    this->model3D = new Model(model);
    this->model = glm::translate(this->model, this->position); // translate it down so it's at the center of the scene
    this->model = glm::scale(this->model, scale);	// it's a bit too big for our scene, so scale it down
}


void Bullet::Update(float deltaTime, Shader shader, float mouseX, float mouseY)  {
    GameObject::Update(deltaTime, shader, mouseX, mouseY);
    float velocity = 10 * deltaTime;
    this->timer -= deltaTime;
    this->model = glm::translate(this->model, this->position * velocity);

    if (this->timer <= 0) {
        this->destroy = true;
    }
}

Bullet::~Bullet()
{

}
