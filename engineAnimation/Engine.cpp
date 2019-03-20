#include "Engine.h"

Engine::Engine() :
	angle(0)
{
}

const vector<Piston>& Engine::getPistons() const
{
	return pistons;
}

const vector<ConnectingRod>& Engine::getConRods() const
{
	return conRods;
}

void Engine::setAngle(GLfloat angle)
{
	this->angle = angle;
	crankShaft.setAngle(angle);
}

GLfloat Engine::getAngle()
{
	return angle;
}

CrankShaft& Engine::getCrankShaft()
{
	return crankShaft;
}

