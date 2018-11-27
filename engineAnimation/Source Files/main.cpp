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
#include "Camera.h"
#include "Piston.h"

const GLuint WIDTH = 800, HEIGHT = 800;

int main()
{
	InitMisc& initializer = InitMisc::getInstance();
	try
	{
		GLFWwindow* window = initializer.initGlfwWindow(WIDTH, HEIGHT);
		Camera camera(window);
		initializer.initGlew();

		// create model, view, projection matrices
		glm::mat4 model;
		//model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 view;
		view = camera.getViewMatrix();

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
		Cylinder cylinder(0.35f, 0.25f);

		// create Pistons
		vector<Piston> pistons = {
			Piston(-1.5f, 0.0f),
			Piston(-0.9f, 0.0f, GLfloat(M_PI / 3)),
			Piston(-0.3f, 0.0f, GLfloat(2 * M_PI / 3)),
			Piston(0.3f, 0.0f, GLfloat(2 * M_PI / 3)),
			Piston(0.9f, 0.0f, GLfloat(M_PI / 3)),
			Piston(1.5f, 0.0f),
		};

		// create renderer
		Renderer renderer;

		glfwSetTime(0.0);
		const GLfloat conRodLen = 0.8f;
		const GLfloat crankRad = 0.2f;
		const GLfloat revs = 100 * (2 * M_PI / 60);

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			GLfloat time = glfwGetTime();

			glfwPollEvents();
			renderer.clear();

			view = camera.getViewMatrix();

			//draw pistons
			for (auto &piston : pistons) {
				piston.setAngle(revs * time);
				renderer.drawPiston(piston, cylinder, theProgram, projection * view, crankRad, conRodLen);
			}

			//draw square
			model = glm::mat4();
			mvp = projection * view * model;
			theProgram.setUniformMatrix4fv("uTransform", mvp);
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