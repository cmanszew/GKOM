#pragma once
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Cylinder.h"

class Piston
{
public:
	Piston(GLfloat x = 0, GLfloat y = 0, GLfloat offset = 0);
	void setY(GLfloat y);
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
};