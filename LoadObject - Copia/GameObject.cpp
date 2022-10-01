#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::GameObject(Model* model3D, glm::vec3 transform)
{
    this->id = reinterpret_cast<uint32_t>(this);
    std::cout << this->id << std::endl;
    this->transform = transform;
    this->model3D = model3D;
    this->model = glm::translate(this->model, this->transform); // translate it down so it's at the center of the scene
    this->model = glm::scale(this->model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
}

void GameObject::Update(float deltaTime, Shader shader, float mouseX, float mouseY)
{
    shader.setMat4("model", this->model);
    this->model3D->Draw(shader);
}


void GameObject::Draw(Shader shader)
{

}

//void GameObject::DestroyByTime()
//{
//    for (int i = 0; i < gameObjects.size(); i++) {
//        if(gameObjects[i]->id == this->id){
//            gameObjects.erase(gameObjects.begin() + i);
//        }
//    }
//}

//void GameObject::SetShader(Shader shader)
//{
//    this->shader = shader;
//}

GameObject::~GameObject()
{
    //delete this->model3D;
    std::cout << "foi" << std::endl;
    //delete this->model3D;
    //delete this;
}
