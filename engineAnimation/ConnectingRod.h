#pragma once
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "EngineConstants.h"

class ConnectingRod
{
public:
//	ConnectingRod(GLfloat x = 0, GLfloat y = 0, GLfloat offset = 0);
	ConnectingRod(GLfloat x = 0, GLfloat offset = 0, GLfloat vAngle = 0);
	void setY(GLfloat y);
	void setTilt(GLfloat tilt);
	void setAngle(GLfloat angle);
	void setPosition(GLfloat crankAngle);
	glm::mat4 getModelMatrix() const;
	GLfloat getAngle();
	GLfloat getOffset();

private:
	GLfloat x;
	GLfloat offset;

	glm::mat4 modelTrans;
	glm::mat4 modelRot;
	glm::mat4 model;
	GLfloat angle;
	//GLfloat tilt;
	GLfloat vAngleHalf;
};