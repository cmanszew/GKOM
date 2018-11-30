#include "ConnectingRod.h"

ConnectingRod::ConnectingRod(GLfloat x, GLfloat offset)
	: x(x), offset(offset), angle(0), modelTrans(), modelRot()
{}

void ConnectingRod::setY(GLfloat y)
{
	modelTrans = glm::translate(glm::mat4(), glm::vec3(x, y, 0));
}

void ConnectingRod::setTilt(GLfloat tilt)
{
	modelRot = glm::rotate(glm::mat4(), tilt, glm::vec3(1.0f, 0.0f, 0.0f));
}

void ConnectingRod::setAngle(GLfloat angle)
{
	this->angle = angle;
}

glm::mat4 ConnectingRod::getModelMatrix() const
{
	return modelRot * modelTrans;
}

const glm::mat4& ConnectingRod::getTransMatrix() const
{
	return modelTrans;
}

const glm::mat4& ConnectingRod::getRotMatrix() const
{
	return modelRot;
}

GLfloat ConnectingRod::getAngle()
{
	return angle;
}

GLfloat ConnectingRod::getOffset()
{
	return offset;
}