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

//const GLuint WIDTH = 800, HEIGHT = 800;
const GLuint WIDTH = 1920, HEIGHT = 1080;

const GLfloat secToRevolution = GLfloat(2 * M_PI / 60);
const GLfloat rpm = 140.0f; //TODO - make this configurable

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

		Cylinder elipse(0.2f, 0.3f, 0.4f);

		glfwSetTime(0.0);

		// GLuint piston_texture = TextureMgr().LoadMipmapTexture(0, "piston_tex.png");
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		int width, height;
		unsigned char* image = SOIL_load_image("piston_tex.png", &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		while (!glfwWindowShouldClose(window))
		{
			GLfloat time = (GLfloat)glfwGetTime();
			time = 0.0f;								// DEBUG PAUSE IS HERE
			glfwPollEvents();
			renderer.clear();

			view = camera.getViewMatrix();

			engine.setAngle(rpm * (secToRevolution * time));
			renderer.drawPistons(engine, projection * view);
			renderer.drawConnectingRods(engine, projection * view);
			renderer.drawCrankShaft(engine, projection * view);

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