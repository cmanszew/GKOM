#pragma once
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Cylinder.h"
#include "shprogram.h"
#include "EngineConstants.h"

class Piston
{
public:
	Piston(GLfloat x = 0, GLfloat offset = 0, GLfloat vAngle = 0);
	void setPosition(GLfloat crankAngle);
	void setAngle(GLfloat angle);
	const glm::mat4& getModelMatrix() const;
	GLfloat getAngle();
	GLfloat getOffset();
	GLfloat getX();

private:
	GLfloat x;
	GLfloat offset;
	glm::mat4 model;
	GLfloat angle;
	GLfloat vAngleHalf;
};