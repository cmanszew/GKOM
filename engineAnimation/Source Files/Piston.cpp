#include "Piston.h"

//Cylinder Piston::cylinder = Cylinder(0.4f, 0.25f); ughhhhh... c++ <3

Piston::Piston(GLfloat x, GLfloat y, GLfloat offset)
	: x(x), offset(offset), angle(0), model()
{
	model = glm::translate(model, glm::vec3(x, y, 0));
}

void Piston::setY(GLfloat y)
{
	this->y = y;
	model = glm::translate(glm::mat4(), glm::vec3(x, y, 0));
}

void Piston::setAngle(GLfloat angle)
{
	this->angle = angle;
}

const glm::mat4& Piston::getModelMatrix() const
{
	return model;
}

GLfloat Piston::getAngle()
{
	return angle;
}

GLfloat Piston::getOffset()
{
	return offset;
}

GLfloat Piston::getX()
{
	return x;
}

GLfloat Piston::getY()
{
	return y;
}
