#include "inlineEngine.h"

inlineEngine::inlineEngine()
	: pistonCylinder(EngConst::pistonHeight, EngConst::cylBore / 2),
	conRodPrism(EngConst::conRodLen, EngConst::conRodThck),
	crankShaftCylinder(EngConst::crankMainShaftComponent, EngConst::crankShaftRad),
	ellipticCylinder(EngConst::rodConnectorThck, EngConst::rodConnectorRadS, EngConst::rodConnectorRadL),
	//ellipticCylinder(EngConst::rodConnectorThck, 1.9f * EngConst::crankShaftRad, 2.4f * EngConst::crankShaftRad),
	shader("shaderTex.vert", "shaderTex.frag")
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


inlineEngine::~inlineEngine()
{
}

Cylinder& inlineEngine::getPistonCylinder()
{
	return pistonCylinder;
}

Prism& inlineEngine::getConRodPrism()
{
	return conRodPrism;
}

ShaderProgram& inlineEngine::getShader()
{
	return shader;
}

Cylinder& inlineEngine::getCrankShaftCylinder()
{
	return crankShaftCylinder;
}

Cylinder& inlineEngine::getEllipticCylinder()
{
	return ellipticCylinder;
}