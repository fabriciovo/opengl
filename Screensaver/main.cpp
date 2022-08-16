#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES              
		0.3f,  -0.3f, 0.0f, 0.0f,
		0.3f, 0.3f, 0.0f, 0.0f, 
		0.0f,  0.0f, 1.0f, 0.0f,
		0.1f,  0.0f, 0.0f, 1.0f,
};



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "Window"
	GLFWwindow* window = glfwCreateWindow(800, 800, "Window", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	//EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 0,NULL );

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	//EBO1.Unbind();


	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Main while loop


	int matrixLocation = glGetUniformLocation(shaderProgram.ID, "matrix");
	float speedY = 1.0f;
	float speedX = 1.0f;

	float lastPosX = 0.0f;
	float lastPosY = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;
		if (elapsedSeconds >= 0.0f) {
			previousSeconds = currentSeconds;
			if (fabs(lastPosX) > 1.0f) {
				speedX = -speedX;

			}
			else if (fabs(lastPosX) <= 0) {
				speedX = speedX;
			}

			if (fabs(lastPosY) < 1.0f) {
				speedY = speedY;

			}
			else if (fabs(lastPosY) >= 0) {
				speedY = -speedY;
			}
	
			vertices[12] = elapsedSeconds * speedX + lastPosX;
			lastPosX = vertices[12];

			vertices[13] = elapsedSeconds * speedY + lastPosY;
			lastPosY = vertices[13];
		}


		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, vertices);

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		// glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	//EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}