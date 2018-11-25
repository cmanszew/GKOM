#include "InitMisc.h"

InitMisc& InitMisc::getInstance()
{
	static InitMisc instance;
	return instance;
}

GLFWwindow* InitMisc::initGlfwWindow(const GLuint width, const GLuint height)
{
	initGlfw();
	GLFWwindow* window = glfwCreateWindow(width, height, "engineAnimation", nullptr, nullptr);
	if (window == nullptr)
		throw exception("GLFW window not created");
	glfwMakeContextCurrent(window);
	//glfwSetKeyCallback(window, key_callback); //TODO

	glViewport(0, 0, width, height); //CAUTION!!! This might be in the wrong place
	glEnable(GL_DEPTH_TEST); //CAUTION!!! This might be in the wrong place
	return window;
}

void InitMisc::initGlew()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw exception("GLEW Initialization failed");
}

InitMisc::InitMisc()
{
}

void InitMisc::initGlfw()
{
	if (glfwInit() != GL_TRUE)
		throw exception("GLFW initialization failed");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void InitMisc::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

