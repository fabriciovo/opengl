#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Player.h"

#include <iostream>
#include "VAO.h"
#include "EBO.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void Shooting(Shader ourShader);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera * camera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool isFirstMouse = false;
std::vector<GameObject*> gameObjects;

float deltaTime = 0.0f;
float lastFrame = 0.0f;


GLfloat lightVertices[] =
{ //     COORDINATES     //
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};



int main()
{
    //glfw: initialize and configure
    //------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FPS", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    //configure global opengl state
    //-----------------------------
    glEnable(GL_DEPTH_TEST);

    //build and compile shaders
    //-------------------------
    Shader ourShader("model_loading.vs", "model_loading.fs");
    Shader lightShader("basic_lighting.vs", "basic_lighting.fs");

    // Shader for light cube
    // Generates Vertex Array Object and binds it
    VAO lightVAO;
    lightVAO.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    // Generates Element Buffer Object and links it to indices
    EBO lightEBO(lightIndices, sizeof(lightIndices));
    // Links VBO attributes such as coordinates and colors to VAO
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    // Unbind all to prevent accidentally modifying them
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader.use();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    //load Game Objects
    //-----------
    GameObject* obj2 = new GameObject("resources/pyramid/pyramid.obj", glm::vec3(10.0f, 14.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 3.0f);
    GameObject* obj3 = new GameObject("resources/curve/curve.obj", glm::vec3(-10.0f, 0.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 5.0f);
    GameObject* obj4 = new GameObject("resources/dragon/dragon.obj", glm::vec3(40.0f, 10.0f, 3.0f), glm::vec3(3.0f, 3.0f, 3.0f), 2.0f);
    GameObject* obj1 = new GameObject("resources/mesa01/mesa01.obj", glm::vec3(5.0f, 0.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f),8.0f);


    Player * player = new Player("resources/cube/cube.obj", glm::vec3(20.0f, 1.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f),camera, window);

    gameObjects.push_back(player);
    gameObjects.push_back(obj2);
    gameObjects.push_back(obj3);
    gameObjects.push_back(obj4);
    gameObjects.push_back(obj1);

    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //Camera
        camera->Inputs(window);
        ourShader.use();
        camera->Matrix(90.0f, 0.1f, 100.0f, ourShader, "camMatrix");

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (isFirstMouse)
            {
                Shooting(ourShader);
                isFirstMouse = false;
            }
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            isFirstMouse = true;
        }

        lightShader.use();
        camera->Matrix(90.0f, 0.1f, 100.0f, lightShader, "camMatrix");

        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        for (int i = 0; i < gameObjects.size(); i++) {
            if (!gameObjects[i]->destroy) {
                gameObjects[i]->Update(deltaTime, lightShader);
                if (gameObjects[i]->Collision(gameObjects)) {
                    gameObjects[i]->destroy = true;
                }
            }
            else {
                delete gameObjects[i];
                gameObjects.erase(gameObjects.begin() + i);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void Shooting(Shader ourShader) {

    Bullet* bullet = new Bullet("resources/cube/cube.obj", camera->Position, glm::vec3(1.0f, 1.0f, 1.0f), camera->Orientation, 2.0f);
    gameObjects.push_back(bullet);
}