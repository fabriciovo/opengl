#include "Bullet.h"


Bullet::Bullet(std::string model, glm::vec3 position, glm::vec3 scale, glm::vec3 dir) : GameObject(model, position, scale) {
    this->dir = dir;
 
}


void Bullet::Update(float deltaTime, Shader shader)  {
    GameObject::Update(deltaTime, shader);
    float velocity = 10 * deltaTime;
    this->timer -= deltaTime;
    this->position += this->dir * velocity;
    if (this->timer <= 0) {
        this->destroy = true;
    }
}

Bullet::~Bullet()
{

}
