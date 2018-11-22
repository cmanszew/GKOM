#define GLEW_STATIC
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shprogram.h"
#include "InitMisc.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "Cylinder.h"

const GLuint WIDTH = 800, HEIGHT = 800;

/* TODO: embed this function into a shape class (f. e. class Cylinder,
and make it generate apropriate vertices. Currently it draws a circle */
void genVertices(vector<GLfloat> &vertices)
{
	const int angle_inc = 5;
	const float radius = 0.3f;

	for (int angle = 0; angle < 360; angle += angle_inc) {
		vertices.push_back(radius * (float)cos((double)angle * M_PI / 180.0));
		vertices.push_back(0.0f);
		vertices.push_back(radius * (float)sin((double)angle * M_PI / 180.0));
	}
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
}

/* TODO: embed this function into a shape class (f. e. class Cylinder,
and make it generate apropriate indices. Currently it draws a circle */
void genIndices(vector<GLuint> &indices, GLuint indCnt)
{	
	for (GLuint i = 0; i < indCnt; ++i) {
		indices.push_back(indCnt);
		indices.push_back(i);
		indices.push_back((i + 1) % indCnt);
		cout << "Drawing: " << indCnt << " " << i << " " << (i + 1) % indCnt << endl;
	}
}

int main()
{
	InitMisc& initializer = InitMisc::getInstance();
	try
	{
		GLFWwindow* window = initializer.initGlfwWindow(WIDTH, HEIGHT);
		initializer.initGlew();

		// create model, view, projection matrices
		glm::mat4 model;
		model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 view;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		glm::mat4 mvp = projection * view * model;

		// create VertexBuffer object
		vector<GLfloat> vertices2 = {
			-1.0f, -1.0f, 0.0f,
			-0.5f,-1.0f, 0.0f,
			-1.0f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
		};
		VertexBuffer vbo2(sizeof(GLfloat) * vertices2.size(), &vertices2[0], GL_STATIC_DRAW);

		// create VertexArray object
		VertexArray vao;
		VertexBufferLayout vbl;
		vbl.pushGLfloat(3);
		vao.associateVertexBuffer(vbo2, vbl);

		// create IndexBuffer object
		vector<GLuint> indices2 = {
			0, 1, 2,
			1, 2, 3,
		};
		IndexBuffer ibo2(indices2.size(), &indices2[0], GL_STATIC_DRAW);
		
		// create ShaderProgram
		ShaderProgram theProgram("Source Files/shader.vert", "Source Files/shader.frag");
		theProgram.setUniform4f("uColor", 0.82f, 0.82f, 0.85f, 1.0f);
		theProgram.setUniformMatrix4fv("uTransform", mvp);

		// create cylinder
		Cylinder cylinder(0.8f, 0.5f);

		// create renderer
		Renderer renderer;

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
			renderer.clear();

			//gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 0.3f, 100, 100);???

			theProgram.setUniform4f("uColor", 0.82f, 0.82f, 0.85f, 1.0f);
			renderer.drawTriangles(cylinder.getVao(), cylinder.getBaseIbo(), theProgram);

			theProgram.setUniform4f("uColor", 0.92f, 0.92f, 0.95f, 1.0f);
			renderer.drawTriangleStrip(cylinder.getVao(), cylinder.getSideIbo(), theProgram);

			renderer.drawTriangles(vao, ibo2, theProgram);

			glfwSwapBuffers(window);
		}
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}