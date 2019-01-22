#pragma once
#define GLEW_STATIC
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
	
class Camera
{
public:
	Camera(GLFWwindow *window);
	static void processInput(GLFWwindow* window, int key, int scancode, int action, int mode);
	glm::mat4 getViewMatrix();

private:
	static glm::vec3 cameraPos;
	static glm::vec3 nextCameraPos;
	static glm::vec3 cameraTarget;
	static glm::vec3 cameraUp;
	static glm::vec3 cameraRight;

	static inline bool keyPressed(int key, int action, int keyCode);

	GLFWwindow *window;
};