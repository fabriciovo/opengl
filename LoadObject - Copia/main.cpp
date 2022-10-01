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

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void Shooting(Shader ourShader);


//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
double xMousePos, yMousePos;

std::vector<GameObject*> gameObjects;

//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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

    //glfw window creation
    //--------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //glad: load all OpenGL function pointers
    //---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    //configure global opengl state
    //-----------------------------
    glEnable(GL_DEPTH_TEST);

    //build and compile shaders
    //-------------------------
    Shader ourShader("model_loading.vs", "model_loading.fs");

    //load Game Objects
    //-----------
    GameObject* obj1 = new GameObject("resources/mesa01/mesa01.obj", glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    GameObject* obj2 = new GameObject("resources/mesa01/mesa01.obj", glm::vec3(20.0f, 1.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    gameObjects.push_back(obj1);
    gameObjects.push_back(obj2);

    //draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //render loop
    //-----------
    while (!glfwWindowShouldClose(window))
    {
        //per-frame time logic
        //--------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Handles camera inputs
        camera.Inputs(window);
        // Updates and exports the camera matrix to the Vertex Shader
        camera.Matrix(90.0f, 0.1f, 100.0f, ourShader, "camMatrix");

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (firstMouse)
            {
                Shooting(ourShader);
                firstMouse = false;
            }
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            firstMouse = true;
        }


        //render
        //------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //don't forget to enable shader before setting uniforms
        ourShader.use();

        
        for (int i = 0; i < gameObjects.size(); i++) {
            if (!gameObjects[i]->destroy) { 
                gameObjects[i]->Update(deltaTime, ourShader, 0, 0); 
            }
            else { 
                delete gameObjects[i];
                gameObjects.erase(gameObjects.begin() + i); 
            }
        }

        //glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        //-------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //glfw: terminate, clearing all previously allocated GLFW resources.
    //------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

//process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//---------------------------------------------------------------------------------------------------------


//glfw: whenever the window size changed (by OS or user resize) this callback function executes
//---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //make sure the viewport matches the new window dimensions; note that width and 
    //height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void Shooting(Shader ourShader) {

    GameObject* shoot = new Bullet("resources/mesa01/mesa01.obj", camera.Position, glm::vec3(1.0f, 1.0f, 1.0f), camera.Orientation);
    gameObjects.push_back(shoot);
}