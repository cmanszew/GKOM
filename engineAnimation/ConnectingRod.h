#pragma once
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ConnectingRod
{
public:
//	ConnectingRod(GLfloat x = 0, GLfloat y = 0, GLfloat offset = 0);
	ConnectingRod(GLfloat x = 0, GLfloat offset = 0);
	void setY(GLfloat y);
	void setTilt(GLfloat tilt);
	void setAngle(GLfloat angle);
	glm::mat4 getModelMatrix() const;
	GLfloat getAngle();
	GLfloat getOffset();

private:
	GLfloat x;
	GLfloat offset;

	glm::mat4 modelTrans;
	glm::mat4 modelRot;
	GLfloat angle;
	GLfloat tilt;
};