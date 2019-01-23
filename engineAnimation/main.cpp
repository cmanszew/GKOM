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
#include "TextureMgr.h"
#include "Ground.h"

//const GLuint WIDTH = 800, HEIGHT = 800;
const GLuint WIDTH = 1920, HEIGHT = 1080;

const GLfloat secToRevolution = GLfloat(2 * M_PI / 60);
const GLfloat rpm = 130.0f; //TODO - make this configurable

int main()
{
	InitMisc& initializer = InitMisc::getInstance();
	try
	{
		GLFWwindow* window = initializer.initGlfwWindow(WIDTH, HEIGHT);
		Camera camera(window);
		initializer.initGlew();

		glm::mat4 model, view;
		glm::mat4 projection(glm::perspective(glm::radians(40.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f));
		//projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.01f, 100.0f);

		Renderer renderer;
		Engine engine;
		Ground ground;
		
		TextureMgr textureManager(0);

		Cylinder elipse(0.2f, 0.3f, 0.4f);

		glfwSetTime(0.0);

		textureManager.addTexture("piston_tex.png", GL_MIRRORED_REPEAT);
		textureManager.addTexture("bruk2.jpg", GL_MIRRORED_REPEAT);
		
		while (!glfwWindowShouldClose(window))
		{
			GLfloat time = (GLfloat)glfwGetTime();
			glfwPollEvents();
			renderer.clear(0.53, 0.81, 0.92);

			view = camera.getViewMatrix();

			engine.setAngle(rpm * (secToRevolution * time));

			renderer.drawPistons(engine, projection * view);
			renderer.drawConnectingRods(engine, projection * view);
			renderer.drawCrankShaft(engine, projection * view);
			renderer.drawGround(ground, projection * view);
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