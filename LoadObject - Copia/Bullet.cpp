#include "Bullet.h"


Bullet::Bullet(std::string model, glm::vec3 position, glm::vec3 scale, glm::vec3 dir) {
    this->position = position;
    this->dir = dir;
    this->model3D = new Model(model);
    this->model = glm::translate(this->model, this->position); // translate it down so it's at the center of the scene
    this->model = glm::scale(this->model, scale);	// it's a bit too big for our scene, so scale it down
}


void Bullet::Update(float deltaTime, Shader shader)  {
    GameObject::Update(deltaTime, shader);
    float velocity = 10 * deltaTime;
    this->timer -= deltaTime;
    this->model = glm::translate(this->model, this->dir * velocity);

    if (this->timer <= 0) {
        this->destroy = true;
    }
}

Bullet::~Bullet()
{

}
