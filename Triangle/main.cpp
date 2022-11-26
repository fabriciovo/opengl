#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "shaderClass.h"


using namespace std;

vector<glm::vec3*>* CreateBSpline(vector<glm::vec3*>* points);


vector<float> points;
vector<float> bSplineCurve;
vector<glm::vec3*>* controlPointsVec = new vector<glm::vec3*>();
vector<glm::vec3*>* selectedPoints = new vector<glm::vec3*>();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


GLuint vaoPoints, vboPoints;
GLuint vaoPointLines, vboPointLines;
GLuint vaoSpline, vboSpline;



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
		cout << "Cursor Position at (" << xpos  << " : " << ypos << endl;
		points.push_back((2.0f * xpos / 800 - 1.0f));
		points.push_back((-2.0f * ypos / 800 + 1.0f));
		points.push_back(0.0f);

		selectedPoints->push_back(new glm::vec3(xpos,ypos,0.0f));

		glBindVertexArray(vaoPoints);
		glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_DYNAMIC_DRAW);

		
		if (points.size() > 9) {

			controlPointsVec = CreateBSpline(selectedPoints);
			//glBindVertexArray(vaoSpline);
			//glBindBuffer(GL_ARRAY_BUFFER, vboSpline);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bSplineCurve.size(), bSplineCurve.data(), GL_STATIC_DRAW);
			//glEnableVertexAttribArray(0);
			//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glBindVertexArray(vaoSpline);
			glBindBuffer(GL_ARRAY_BUFFER, vboSpline);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bSplineCurve.size(), bSplineCurve.data(), GL_DYNAMIC_DRAW);

		}


	}
}



int main()
{
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "window", NULL, NULL);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	gladLoadGL();
	Shader shaderProgram("default.vert", "default.frag");
	//glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	//glm::mat4 projection = glm::ortho(0, 800, 800, 0, -1, 1);


	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glGenBuffers(1, &vboPoints);
	glGenVertexArrays(1, &vaoPoints);
	glBindVertexArray(vaoPoints);
	glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);



	glGenBuffers(1, &vboSpline);
	glGenVertexArrays(1, &vaoSpline);
	glBindVertexArray(vaoSpline);
	glBindBuffer(GL_ARRAY_BUFFER, vboSpline);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);


	glPointSize(15);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		shaderProgram.Activate();
		//glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(vaoPoints);
		glDrawArrays(GL_POINTS, 0, points.size() / 3);
		//glDrawArrays(GL_LINE_STRIP, 0, points.size() / 3);

		glBindVertexArray(vaoSpline);
		glDrawArrays(GL_LINE_STRIP, 0, bSplineCurve.size() / 3);



		//glDrawArrays(GL_LINE_STRIP, 0, bSplineCurve.size() / 3);
		//glBindVertexArray(vaoSpline);
		////glBindBuffer(GL_ARRAY_BUFFER, vboSpline);
		////glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bSplineCurve.size(), bSplineCurve.data(), GL_STATIC_DRAW);
		////glEnableVertexAttribArray(0);
		////glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		//glBindVertexArray(vaoSpline);
		//glDrawArrays(GL_LINE_STRIP, 0, bSplineCurve.size() / 3);

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