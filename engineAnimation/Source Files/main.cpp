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
#include "Prism.h"
#include "ConnectingRod.h"

const GLuint WIDTH = 800, HEIGHT = 800;

const GLfloat cylBore = 0.5f;
const GLfloat cylStroke = 0.6f;
const GLfloat cylSpacing = cylBore + 0.15f;
const GLfloat conRodLen = 0.7f;
const GLfloat conRodThck = 0.1f;
const GLfloat crankRad = cylStroke / 2.0f;
const GLfloat crankPinRad = 0.05f; //TODO: pass this to Renderer::drawConnectingRod
const GLfloat crankShaftRad = 0.12f;
const GLfloat secToRevolution = GLfloat(2 * M_PI / 60);
const GLfloat piston1x = -5.0f / 2.0f * (cylSpacing);

const GLfloat rpm = 200.0f; //TODO - make this configurable

int main()
{
	InitMisc& initializer = InitMisc::getInstance();
	try
	{
		GLFWwindow* window = initializer.initGlfwWindow(WIDTH, HEIGHT);
		Camera camera(window);
		initializer.initGlew();

		// create model, view, projection matrices
		glm::mat4 model, view;
		glm::mat4 projection(glm::perspective(glm::radians(40.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f));
		//projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.01f, 100.0f);
		
		// create ShaderProgram
		ShaderProgram theProgram("Source Files/shader.vert", "Source Files/shader.frag");

		// create cylinder
		Cylinder cylinder(0.35f, cylBore / 2);
		Cylinder cylinder2(cylSpacing - conRodThck, crankShaftRad);

		// create Pistons
		vector<Piston> pistons = {
			Piston(piston1x, 0.0f),
			Piston(piston1x + cylSpacing, 0.0f, GLfloat(-M_PI / 3)),
			Piston(piston1x + 2 * cylSpacing, 0.0f, GLfloat(-2 * M_PI / 3)),
			Piston(piston1x + 3 * cylSpacing, 0.0f, GLfloat(-2 * M_PI / 3)),
			Piston(piston1x + 4 * cylSpacing, 0.0f, GLfloat(-M_PI / 3)),
			Piston(piston1x + 5 * cylSpacing, 0.0f),
		};

		// create rod
		Prism prism(conRodLen);
		vector<ConnectingRod> rods = {
			ConnectingRod(pistons[0].getX(), pistons[0].getOffset()),
			ConnectingRod(pistons[1].getX(), pistons[1].getOffset()),
			ConnectingRod(pistons[2].getX(), pistons[2].getOffset()),
			ConnectingRod(pistons[3].getX(), pistons[3].getOffset()),
			ConnectingRod(pistons[4].getX(), pistons[4].getOffset()),
			ConnectingRod(pistons[5].getX(), pistons[5].getOffset()),
		};

		// create renderer
		Renderer renderer;

		glfwSetTime(0.0);
		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			GLfloat time = (GLfloat)glfwGetTime();

			glfwPollEvents();
			renderer.clear();

			view = camera.getViewMatrix();

			// draw pistons
			for (auto &piston : pistons) {
				piston.setAngle(rpm * (secToRevolution * time));
				renderer.drawPiston(piston, cylinder, theProgram, projection * view, crankRad, conRodLen);
			}

			// draw rods
			theProgram.setUniform4f("uColor", 0.76f, 0.76f, 0.76f, 1.0f);
			for (auto &conRod : rods) {
				conRod.setAngle(rpm * (secToRevolution * time));
				renderer.drawConnectingRod(conRod, prism, theProgram, projection * view, crankRad, conRodLen);
			}

			// draw crank
			//model = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			//theProgram.setUniformMatrix4fv("uTransform", projection * view * model);
			//renderer.drawCylinder(cylinder2, theProgram);

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