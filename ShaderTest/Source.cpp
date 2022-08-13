/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle */

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int setupGeometry();

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola transfoms!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	Shader shader("./shaders/transformations.vs", "./shaders/transformations.frag");

	GLuint VAO = setupGeometry();

	GLint colorLoc = glGetUniformLocation(shader.ID, "contourColor");
	assert(colorLoc > -1);
	glUseProgram(shader.ID);
	glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f); 


	GLint rasterCodeLoc = glGetUniformLocation(shader.ID, "rasterCode");

	glEnable(GL_DEPTH);

	while (!glfwWindowShouldClose(window))
	{
		
		glfwPollEvents();


		glClearColor(0.8f, 0.8f, 0.8f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT);


		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glm::mat4 model = glm::mat4(1);


		model = glm::translate(model, glm::vec3(400.0f, 300.0f, 0.0f));


		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));


		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 1.0f));

		glm::mat4 ortho = glm::mat4(1);
		ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);


		GLint modelLoc = glGetUniformLocation(shader.ID, "model");
		GLint projLoc = glGetUniformLocation(shader.ID, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));



		glLineWidth(5);
		glPointSize(10);

		glUniform1i(rasterCodeLoc, 0);
		glUseProgram(shader.ID);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glUniform1i(rasterCodeLoc, 1); 
		glDrawArrays(GL_LINE_LOOP, 0, 6);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


int setupGeometry()
{

	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f, 1.0, 0.0, 0.0, 
		0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0, 
	   -0.5f,  0.5f, 0.0f, 0.0, 0.0, 1.0, 


		0.5f, -0.5f, 0.0f, 1.0, 1.0, 0.0,
	   -0.5f, -0.5f, 0.0, 1.0, 0.0, 1.0,  
	   -0.5f,  0.5f, 0.0f, 0.0, 1.0, 1.0
	};

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), ((GLvoid*)(3 * sizeof(GLfloat))));
	glEnableVertexAttribArray(1);





	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);

	return VAO;
}

