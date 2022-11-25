#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

#define PI  3.14159265359
#define HALF_PI PI/2.0


vector<float> points;
vector<float> bSplineCurve;
vector<glm::vec3*>* controlPointsVec = new vector<glm::vec3*>();
vector<glm::vec3*>* selectedPoints = new vector<glm::vec3*>();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

GLuint vaoC, vboC, vboColors;
GLuint vaoI, vboI;
GLuint vaoE, vboE;
GLuint vaoB, vboB;




vector<glm::vec3*>* CreateBSpline(vector<glm::vec3*>* points) {

	bSplineCurve.clear();
	vector<glm::vec3*>* bspline = new vector<glm::vec3*>();
	vector<glm::vec3*>* temp = new vector<glm::vec3*>();
	vector<glm::vec3*>* temp2 = new vector<glm::vec3*>();

	int size = points->size();
	for (int i = 0; i < size; i++) {
		temp->push_back(new glm::vec3(points->at(i)->x, points->at(i)->y, points->at(i)->z));
	}


	temp->push_back(points->at(0));
	temp->push_back(points->at(1));
	temp->push_back(points->at(2));


	for (int i = 0; i < (temp->size() - 3); i++) {

		for (int j = 0; j < 100; ++j) {

			float t = static_cast<float>(j) / 99.0;

			GLfloat x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * temp->at(i)->x +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * temp->at(i + 1)->x +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * temp->at(i + 2)->x +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * temp->at(i + 3)->x) / 6);

			GLfloat y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * temp->at(i)->y +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * temp->at(i + 1)->y +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * temp->at(i + 2)->y +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * temp->at(i + 3)->y) / 6);

			GLfloat z = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * temp->at(i)->z +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * temp->at(i + 1)->z +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * temp->at(i + 2)->z +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * temp->at(i + 3)->z) / 6);

			glm::vec3* point = new glm::vec3(x, y, z);
			bspline->push_back(point);
			bSplineCurve.push_back(x);
			bSplineCurve.push_back(y);
			bSplineCurve.push_back(z);
		}
	}

	return bspline;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		cout << "Cursor Position at (" << xpos << " : " << ypos << endl;
		points.push_back(xpos);
		points.push_back(ypos);
		points.push_back(0.0f);

		selectedPoints->push_back(new glm::vec3(xpos,ypos,0.0f));

		glBindVertexArray(vaoC);
		glBindBuffer(GL_ARRAY_BUFFER, vboC);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		
		if (points.size() > 9) {

			controlPointsVec = CreateBSpline(selectedPoints);
			glBindVertexArray(vaoB);
			glBindBuffer(GL_ARRAY_BUFFER, vboB);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bSplineCurve.size(), bSplineCurve.data(), GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		}


	}
}


void draw() {

	glBindVertexArray(vaoC);
	glBindBuffer(GL_ARRAY_BUFFER, vboC);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_POINTS, 0, points.size() / 3);

	glBindVertexArray(vaoB);
	glBindBuffer(GL_ARRAY_BUFFER, vboB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bSplineCurve.size(), bSplineCurve.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(vaoB);
	glDrawArrays(GL_LINE_STRIP, 0, bSplineCurve.size() / 3);
}

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

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "window", NULL, NULL);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

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



	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{

		glEnable(GL_POINTS);
		glPointSize(15);
		// shader.setMat4("projection", projection);
		/*glDrawArrays(GL_POINTS, 0, finalPointsFloat.size());
		glDrawArrays(GL_LINE_STRIP, 0, finalPointsFloat.size() / 3);*/
		draw();
		glDisable(GL_POINTS);
		glfwSwapBuffers(window);
		
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}