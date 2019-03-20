#include "Piston.h"

Piston::Piston(GLfloat x, GLfloat offset, GLfloat vAngle)
	: x(x), offset(offset), angle(0), model(), vAngleHalf(vAngle)
{
	model = glm::translate(model, glm::vec3(x, 0, 0));
}

void Piston::setPosition(GLfloat crankAngle)
{
	double crankPinY = EngConst::crankRad * sin(crankAngle + offset - vAngleHalf);
	double crankPinZ = EngConst::crankRad * cos(crankAngle + offset - vAngleHalf);
	float y = GLfloat(crankPinY + sqrt(pow(EngConst::conRodLen, 2) - pow(crankPinZ, 2)));
	model = glm::rotate(glm::mat4(), -vAngleHalf, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(this->x, y, 0));
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

