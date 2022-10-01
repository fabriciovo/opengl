#include "Bullet.h"


Bullet::Bullet(Model* model3D, glm::vec3 transform) {
    this->model3D = model3D;
    this->transform = transform;
    this->model = glm::translate(this->model, transform); // translate it down so it's at the center of the scene
    this->model = glm::scale(this->model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
}


void Bullet::Update(float deltaTime, Shader shader, float mouseX, float mouseY)  {
    GameObject::Update(deltaTime, shader, mouseX, mouseY);
    this->timer -= deltaTime;
    float velocity = 10 * deltaTime;
    shader.setMat4("model", this->model);
    this->model3D->Draw(shader);
    this->model = glm::translate(model, this->transform * velocity);


    if (this->timer <= 0) {
        this->destroy = true;
    }
}

Bullet::~Bullet()
{

}
