#include "Shoot.h"


Shoot::Shoot(Model* model3D, glm::vec3 transform)
{
    this->model3D = model3D;
    this->model = glm::translate(this->model, transform); // translate it down so it's at the center of the scene
    this->model = glm::scale(this->model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
}

void Shoot::Update(float deltaTime, Shader shader)
{
    float velocity = 100 * deltaTime;
    shader.setMat4("model", this->model);

    this->model3D->Draw(shader);
    this->model = glm::translate(model, glm::vec3(0.0f, velocity, 3.0f));



}
