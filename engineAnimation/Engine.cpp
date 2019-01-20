#include "Engine.h"

Engine::Engine()
	: pistonCylinder(EngConst::pistonHeight, EngConst::cylBore / 2),
	conRodPrism(EngConst::conRodLen, EngConst::conRodThck),
	crankShaftCylinder(EngConst::crankMainShaftComponent, EngConst::crankShaftRad),
	ellipticCylinder(EngConst::rodConnectorThck, EngConst::rodConnectorRadS, EngConst::rodConnectorRadL),
	//ellipticCylinder(EngConst::rodConnectorThck, 1.9f * EngConst::crankShaftRad, 2.4f * EngConst::crankShaftRad),
	shader("shader.vert", "shader.frag"),
	angle(0)
{
	offsets = {
		0.0f,
		GLfloat(-2.0f * M_PI / 3.0f),
		GLfloat(-4.0f * M_PI / 3.0f),
		GLfloat(-4.0f * M_PI / 3.0f),
		GLfloat(-2.0f * M_PI / 3.0f),
		0.0f,
	};

	for (unsigned int i = 0; i < offsets.size(); ++i)
		pistons.push_back(Piston(EngConst::piston1x + i * EngConst::cylSpacing, offsets[i]));

	for (unsigned int i = 0; i < pistons.size(); ++i)
		conRods.push_back(ConnectingRod(pistons[i].getX(), pistons[i].getOffset()));

	crankShaft.setup(pistons.size(), offsets);
}

const Cylinder& Engine::getPistonCylinder() const
{
	return pistonCylinder;
}

const vector<Piston>& Engine::getPistons() const
{
	return pistons;
}

const Prism& Engine::getConRodPrism() const
{
	return conRodPrism;
}

const vector<ConnectingRod>& Engine::getConRods() const
{
	return conRods;
}

ShaderProgram& Engine::getShader()
{
	return shader;
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

const Cylinder& Engine::getCrankShaftCylinder() const
{
	return crankShaftCylinder;
}

const Cylinder& Engine::getEllipticCylinder() const
{
	return ellipticCylinder;
}

CrankShaft& Engine::getCrankShaft()
{
	return crankShaft;
}

