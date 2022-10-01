#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Camera.h"
class Player : public GameObject
{
public:
	Player(std::string model, glm::vec3 transform, glm::vec3 scale, Camera * camera, GLFWwindow* window);
	void Update(float deltaTime, Shader shader);
	~Player();

private:
	bool isFirstMouse = false;
	Camera* camera;
	GLFWwindow* window;

};

#endif