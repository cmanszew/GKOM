#include "Engine.h"

const GLfloat Engine::cylBore = 0.5f; //param
const GLfloat Engine::pistonStroke = 0.6f; //param
const GLfloat Engine::pistonHeight = 0.35f; //param
const GLfloat Engine::conRodLen = 0.7f; //param

const GLfloat Engine::conRodThck = 0.15f; //0.1f;
const GLfloat Engine::crankPinRad = 0.05f; //TODO: pass this to Renderer::drawConnectingRod
const GLfloat Engine::crankShaftRad = 0.12f;// 16f;

const GLfloat Engine::cylSpacing = cylBore + 0.1f;
const GLfloat Engine::piston1x = -5.0f / 2.0f * (cylSpacing);
const GLfloat Engine::crankX = piston1x - cylSpacing / 2;
const GLfloat Engine::crankRad = pistonStroke / 2.0f;
const GLfloat Engine::crankMainShaftComponent = cylSpacing - 3 * conRodThck;

Engine::Engine()
	: pistonCylinder(pistonHeight, cylBore / 2),
	conRodPrism(conRodLen, conRodThck),
	crankShaftCylinder(crankMainShaftComponent, crankShaftRad),
	ellipticCylinder(conRodThck, 1.9f *crankShaftRad, 2.4f * crankShaftRad),
	shader("../engineAnimation/Source Files/shader.vert", "../engineAnimation/Source Files/shader.frag"),
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

	for (int i = 0; i < offsets.size(); ++i)
		pistons.push_back(Piston(piston1x + i * cylSpacing, offsets[i]));

	for (unsigned int i = 0; i < pistons.size(); ++i)
		conRods.push_back(ConnectingRod(pistons[i].getX(), pistons[i].getOffset()));

	crankShaft.setup(crankX, cylSpacing, pistons.size(), offsets);
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

