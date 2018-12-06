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
#include "CrankShaft.h"

const GLuint WIDTH = 800, HEIGHT = 800;
//const GLuint WIDTH = 1920, HEIGHT = 1080;

const GLfloat cylBore = 0.5f;
const GLfloat cylStroke = 0.6f;
const GLfloat cylSpacing = cylBore + 0.1f;
const GLfloat conRodLen = 0.7f;
const GLfloat conRodThck = 0.15f; //0.1f;
const GLfloat crankPinRad = 0.05f; //TODO: pass this to Renderer::drawConnectingRod
const GLfloat crankShaftRad = 0.12f;// 16f;

const GLfloat secToRevolution = GLfloat(2 * M_PI / 60);
const GLfloat piston1x = -5.0f / 2.0f * (cylSpacing);
const GLfloat crankX = piston1x - cylSpacing / 2;
const GLfloat crankRad = cylStroke / 2.0f;
const GLfloat crankMainShaftComponent = cylSpacing - 3 * conRodThck;

const GLfloat rpm = 150.0f; //TODO - make this configurable

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
		ShaderProgram theProgram("../engineAnimation/Source Files/shader.vert", "../engineAnimation/Source Files/shader.frag");

		// create Pistons
		Cylinder cylinder(0.35f, cylBore / 2);//TODO
		vector<Piston> pistons = {
			Piston(piston1x, 0.0f),
			Piston(piston1x + cylSpacing, 0.0f, GLfloat(-2.0f * M_PI / 3.0f)),
			Piston(piston1x + 2 * cylSpacing, 0.0f, GLfloat(-4.0f * M_PI / 3.0f)),
			Piston(piston1x + 3 * cylSpacing, 0.0f, GLfloat(-4.0f * M_PI / 3.0f)),
			Piston(piston1x + 4 * cylSpacing, 0.0f, GLfloat(-2.0f * M_PI / 3.0f)),
			Piston(piston1x + 5 * cylSpacing, 0.0f),
		};
		//pistons = {
		//	Piston(piston1x, 0.0f),
		//	Piston(piston1x + cylSpacing, 0.0f, GLfloat(M_PI)),
		//	Piston(piston1x + 2 * cylSpacing, 0.0f, GLfloat(M_PI)),
		//	Piston(piston1x + 3 * cylSpacing, 0.0f),
		//}; //four cyllinder layout

		// create rod
		Prism prism(conRodLen, conRodThck);
		vector<ConnectingRod> rods;
		for (unsigned int i = 0; i < pistons.size(); ++i)
			rods.push_back(ConnectingRod(pistons[i].getX(), pistons[i].getOffset()));

		// create crankShaft
		Cylinder cylinder2(crankMainShaftComponent, crankShaftRad);
		Cylinder elipse2(conRodThck, 1.9f *crankShaftRad, 2.4f * crankShaftRad);
		vector<GLfloat> offsets;
		for (unsigned int i = 0; i < pistons.size(); ++i)
			offsets.push_back(pistons[i].getOffset());
		CrankShaft crankShaft(crankX, cylSpacing, pistons.size(), offsets);

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
			for (auto &conRod : rods) {
				conRod.setAngle(rpm * (secToRevolution * time));
				renderer.drawConnectingRod(conRod, prism, theProgram, projection * view, crankRad, conRodLen);
			}

			// draw crank
			crankShaft.setAngle(rpm * (secToRevolution * time));
			renderer.drawCrankShaft(crankShaft, cylinder2, elipse2, theProgram, projection * view);

			glfwSwapBuffers(window);
		}
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
		getchar();
	}
	glfwTerminate();

	return 0;
}