#include "Camera.h"

glm::vec3 Camera::cameraPos = glm::vec3(-4.5f, 2.5f, 3.0f);
glm::vec3 Camera::cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Camera::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Camera::cameraRight = glm::normalize(glm::cross(cameraTarget - cameraPos, cameraUp));

static const float minAng = 1.0f;
static const float maxAng = 179.0f;
static const float minDist = 1.0f;

Camera::Camera(GLFWwindow *window)
	: window(window)
{
	glfwSetKeyCallback(window, processInput);
}

void Camera::processInput(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	float posAngle = glm::degrees(glm::angle(glm::normalize(cameraUp), glm::normalize(cameraPos)));
	float angle = glm::radians(5.0f);
	float step = 0.1f;

	//cout << "x=" << cameraPos.x << " y=" << cameraPos.y << " z=" << cameraPos.z << endl;
	//cout << "angle=" << posAngle << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (keyPressed(key, action, GLFW_KEY_UP) && posAngle > glm::degrees(angle) + minAng) {
		cameraRight = glm::normalize(glm::cross(cameraTarget - cameraPos, cameraUp));
		cameraPos = glm::rotate(cameraPos, -angle, cameraRight);
	} else if (keyPressed(key, action, GLFW_KEY_DOWN) && posAngle < maxAng - glm::degrees(angle)) {
		cameraRight = glm::normalize(glm::cross(cameraTarget - cameraPos, cameraUp));
		cameraPos = glm::rotate(cameraPos, angle, cameraRight);
	} else if (keyPressed(key, action, GLFW_KEY_LEFT)) {
		cameraPos = glm::rotateY(cameraPos, -angle);
	} else if (keyPressed(key, action, GLFW_KEY_RIGHT)) {
		cameraPos = glm::rotateY(cameraPos, angle);
	} else if (keyPressed(key, action, GLFW_KEY_W) && glm::length(cameraPos) > step + minDist) {
		cameraPos -= step * glm::normalize(cameraPos);
	} else if (keyPressed(key, action, GLFW_KEY_S)) {
		cameraPos += step * glm::normalize(cameraPos);
	}
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPos, cameraTarget, cameraUp);
}

bool Camera::keyPressed(int key, int action, int keyCode)
{
	return key == keyCode && (action == GLFW_PRESS || action == GLFW_REPEAT);
}