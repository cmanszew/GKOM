#include "ConnectingRod.h"

ConnectingRod::ConnectingRod(GLfloat x, GLfloat offset, GLfloat vAngle)
	: x(x), offset(offset), angle(0), modelTrans(), modelRot(), vAngleHalf(vAngle)
{}

void ConnectingRod::setAngle(GLfloat angle)
{
	this->angle = angle;
}

void ConnectingRod::setPosition(GLfloat crankAngle)
{
	double crankPinY = EngConst::crankRad * sin(crankAngle + this->offset - vAngleHalf);
	double crankPinZ = EngConst::crankRad * cos(crankAngle + this->offset - vAngleHalf);

	model = glm::rotate(glm::mat4(), -vAngleHalf, glm::vec3(1.0f, 0.0f, 0.0f));

	GLfloat y = (GLfloat(crankPinY + sqrt(pow(EngConst::conRodLen, 2) - pow(crankPinZ, 2)) - EngConst::crankPinRad));
	model = glm::translate(model, glm::vec3(this->x, y, 0.0f));

	GLfloat tilt = GLfloat(-asin(crankPinZ / EngConst::conRodLen));
	model = glm::rotate(model, tilt, glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::mat4 ConnectingRod::getModelMatrix() const
{
	return model;
}

GLfloat ConnectingRod::getAngle()
{
	return angle;
}

GLfloat ConnectingRod::getOffset()
{
	return offset;
}