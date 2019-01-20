#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

class InitMisc
{
public:
	static InitMisc& getInstance();
	GLFWwindow* initGlfwWindow(const GLuint width, const GLuint height);
	void initGlew();

private:
	InitMisc();
	InitMisc(const InitMisc&) = delete;
	InitMisc& operator=(const InitMisc&) = delete;
	void initGlfw();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

