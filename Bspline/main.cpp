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
#include "objWriterNew.hpp"

#define PI  3.14159265359

using namespace std;

void CreateBSpline(vector<glm::vec3*>* points);
void CreateExternal(vector<glm::vec3*>* points);
void CreateInternal(vector<glm::vec3*>* points);
void keyboard_button_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

vector<glm::vec3*>* bSplineCurveVec = new vector<glm::vec3*>();
vector<glm::vec3*>* vecExternal = new vector<glm::vec3*>();
vector<glm::vec3*>* vecInternal = new vector<glm::vec3*>();

vector<float> points;
vector<float> cinternal;
vector<float> cexternal;
vector<float> bSplineCurve;
bool showExtarnalsCurves = false;


vector<glm::vec3*>* selectedPoints = new vector<glm::vec3*>();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


GLuint vaoPoints, vboPoints;
GLuint vaoSpline, vboSpline;
GLuint vaoExternal, vboExternal;
GLuint vaoInternal, vboInternal;

int faces = 0;
int tamanhoCurvaInterna = 0;
int tamanhoCurvaExterna = 0;
int indexFile = 0;

void CreateBSpline(vector<glm::vec3*>* points) {

	bSplineCurve.clear();
	vector<glm::vec3*>* temp = new vector<glm::vec3*>();

	int size = points->size();
	for (int i = 0; i < size; i++) {
		temp->push_back(new glm::vec3(points->at(i)->x, points->at(i)->y, points->at(i)->z));
	}
 
	temp->push_back(points->at(0));
	temp->push_back(points->at(1));
	temp->push_back(points->at(2));

	int inc = 1/100;
	int N = temp->size() - 3;
	for (int i = 0; i < (temp->size() - 3); i++) { 

		for (int j = 0; j < 100; ++j) {

			float t = static_cast<float>(j) / 99.0;

			GLfloat x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * temp->at(i)->x +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * temp->at((i + 1) % N)->x +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * temp->at((i + 2) % N)->x +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * temp->at((i + 3) % N)->x) / 6);

			GLfloat y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * temp->at(i)->y +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * temp->at((i + 1) % N)->y +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * temp->at((i + 2) % N)->y +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * temp->at((i + 3) % N)->y) / 6);
				bSplineCurveVec->push_back(new glm::vec3(x, y, 0));
				bSplineCurve.push_back(x);
				bSplineCurve.push_back(y);
				bSplineCurve.push_back(0.0f);
		}
	}

	
}

void CreateExternal(vector<glm::vec3*>* points) {
	cexternal.clear();
	vecExternal->clear();
	for (int j = 0; j < points->size() - 1; j += 2) {

		glm::vec3* a = points->at(j);
		glm::vec3* b;

		if (j == points->size() - 2) {
			b = points->at(0);
		}
		else {
			b = points->at(j + 2);
		}

		GLfloat w = b->x - a->x;
		GLfloat h = b->y - a->y;

		if (w == 0 || h == 0) {
			w = b->x - points->at(j - 2)->x;
			h = b->y - points->at(j - 2)->y;
		}
		GLfloat angle = glm::atan(h, w);
		angle += PI / 2.0;
		GLfloat cx = (glm::cos(angle) * 0.1);
		GLfloat cy = (glm::sin(angle) * 0.1);

		glm::vec3* pointGenerated = new glm::vec3(a->x + cx, a->y + cy, 0.0);
		vecExternal->push_back(pointGenerated);

	}

	vecExternal->push_back(vecExternal->at(0));
	vecExternal->push_back(vecExternal->at(1));
	vecExternal->push_back(vecExternal->at(2));


	for (int i = 0; i < vecExternal->size() - 1; i++)
	{

		cexternal.push_back(vecExternal->at(i)->x);
		cexternal.push_back(vecExternal->at(i)->y);
		cexternal.push_back(vecExternal->at(i)->z);

	}

}

void CreateInternal(vector<glm::vec3*>* points) {
	cinternal.clear();
	vecInternal->clear();


	for (int j = 0; j < points->size() - 1; j += 2) {

		glm::vec3* a = points->at(j);
		glm::vec3* b;

		if (j == points->size() - 2) {
			b = points->at(0);
		}
		else {
			b = points->at(j + 2);
		}

		GLfloat w = b->x - a->x;
		GLfloat h = b->y - a->y;

		if (w == 0 || h == 0) {
			w = b->x - points->at(j - 2)->x;
			h = b->y - points->at(j - 2)->y;
		}

		GLfloat angle = glm::atan(h, w);


		angle -= PI / 2.0;



		GLfloat cx = (glm::cos(angle) * 0.1);
		GLfloat cy = (glm::sin(angle) * 0.1);

		glm::vec3* pointGenerated = new glm::vec3(a->x + cx, a->y + cy, 0);
		vecInternal->push_back(pointGenerated);

	}

	vecInternal->push_back(vecInternal->at(0));
	vecInternal->push_back(vecInternal->at(1));
	vecInternal->push_back(vecInternal->at(2));


	for (int i = 0; i < vecInternal->size() - 1; i++)
	{
		cinternal.push_back(vecInternal->at(i)->x);
		cinternal.push_back(vecInternal->at(i)->y);
		cinternal.push_back(vecInternal->at(i)->z);
	}

}

void keyboard_button_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		showExtarnalsCurves = !showExtarnalsCurves;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		OBJWriter obj;
		obj.createMtlFile();
		obj.createOBJFile();
		
		obj.addPointsCurve(vecExternal);

		obj.addPointsCurve(vecInternal);
		
		obj.saveTextureValuesToOBJ();

		obj.addNormalExternalCurve(vecInternal->size());



		obj.addFaces(vecInternal->size());
	


	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		
		double xpos, ypos;
		double realXpos, realYpos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		cout << "Cursor Position at (" << xpos  << " : " << ypos << endl;
		realXpos = 2.0f * xpos / 800 - 1.0f;
		realYpos = -2.0f * ypos / 800 + 1.0f;

		points.push_back(realXpos);
		points.push_back(realYpos);
		points.push_back(0.0f);

		selectedPoints->push_back(new glm::vec3(realXpos, realYpos,0.0f));

		glBindVertexArray(vaoPoints);
		glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_DYNAMIC_DRAW);
		
		if (points.size() > 9) {
			
			bSplineCurveVec->clear();

			//Bspline
			CreateBSpline(selectedPoints);
			glBindVertexArray(vaoSpline);
			glBindBuffer(GL_ARRAY_BUFFER, vboSpline);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bSplineCurve.size(), bSplineCurve.data(), GL_DYNAMIC_DRAW);

			//Create External
			CreateExternal(bSplineCurveVec);
			glBindVertexArray(vaoExternal);
			glBindBuffer(GL_ARRAY_BUFFER, vboExternal);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cexternal.size(), cexternal.data(), GL_DYNAMIC_DRAW);

			//Create Internal
			CreateInternal(bSplineCurveVec);
			glBindVertexArray(vaoInternal);
			glBindBuffer(GL_ARRAY_BUFFER, vboInternal);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cinternal.size(), cinternal.data(), GL_DYNAMIC_DRAW);


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
	glfwSetKeyCallback(window, keyboard_button_callback);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	gladLoadGL();
	Shader shaderProgram("default.vert", "default.frag");
	glEnable(GL_COLOR);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//ObjWritter


	//Points
	glGenBuffers(1, &vboPoints);
	glGenVertexArrays(1, &vaoPoints);
	glBindVertexArray(vaoPoints);
	glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	//bspline
	glGenBuffers(1, &vboSpline);
	glGenVertexArrays(1, &vaoSpline);
	glBindVertexArray(vaoSpline);
	glBindBuffer(GL_ARRAY_BUFFER, vboSpline);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	//internal
	glGenBuffers(1, &vboInternal);
	glGenVertexArrays(1, &vaoInternal);
	glBindVertexArray(vaoInternal);
	glBindBuffer(GL_ARRAY_BUFFER, vboInternal);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	//external
	glGenBuffers(1, &vboExternal);
	glGenVertexArrays(1, &vaoExternal);
	glBindVertexArray(vaoExternal);
	glBindBuffer(GL_ARRAY_BUFFER, vboExternal);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glPointSize(15);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		glBindVertexArray(vaoPoints);
		glDrawArrays(GL_POINTS, 0, points.size() / 3);
		glDrawArrays(GL_LINE_STRIP, 0, points.size() / 3);

		glBindVertexArray(vaoSpline);
		glDrawArrays(GL_LINE_STRIP, 0, bSplineCurve.size() / 3);

		if (showExtarnalsCurves) {
			glBindVertexArray(vaoInternal);
			glDrawArrays(GL_LINE_STRIP, 0, cinternal.size() / 3);

			glBindVertexArray(vaoExternal);
			glDrawArrays(GL_LINE_STRIP, 0, cexternal.size() / 3);
		}
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
