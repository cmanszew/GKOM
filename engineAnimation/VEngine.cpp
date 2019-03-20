#include "VEngine.h"



VEngine::VEngine(GLfloat vAngle) :
	pistonCylinder(EngConst::pistonHeight, EngConst::cylBore / 2),
	conRodPrism(EngConst::conRodLen, EngConst::conRodThck),
	crankShaftCylinder(EngConst::crankMainShaftComponent - EngConst::conRodThck, EngConst::crankShaftRad),
	ellipticCylinder(EngConst::rodConnectorThck, EngConst::rodConnectorRadS, EngConst::rodConnectorRadL),
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
	
	//offsets = {
	//	0.0f,
	//	GLfloat(M_PI),
	//	GLfloat(M_PI),
	//	0.0f,
	//};

	//offsets = {
	//	0.0f,
	//	GLfloat(M_PI / 2.0f),
	//	GLfloat(-M_PI / 2.0f),
	//	GLfloat(M_PI),
	//};

	offsets = {
		0.0f,
		GLfloat(-2.0f * M_PI / 3.0f),
		GLfloat(-4.0f * M_PI / 3.0f),
	};

	pistons.clear();
	for (unsigned int i = 0; i < offsets.size(); ++i) {
		pistons.push_back(Piston(EngConst::piston1x + i * EngConst::cylSpacing - EngConst::conRodThck / 2.0f, offsets[i], vAngle / 2.0f));
		pistons.push_back(Piston(EngConst::piston1x + EngConst::conRodThck / 2.0f + i * EngConst::cylSpacing, offsets[i], -vAngle / 2.0f));
	}

	conRods.clear();
	for (unsigned int i = 0; i < pistons.size() / 2; ++i) {
		conRods.push_back(ConnectingRod(pistons[2 * i].getX(), pistons[2 * i].getOffset(), vAngle / 2.0f));
		conRods.push_back(ConnectingRod(pistons[2 * i + 1].getX(), pistons[2 * i + 1].getOffset(), -vAngle / 2.0f));
	}

	crankShaft.setup(pistons.size() / 2, offsets, 2.0f);
}

VEngine::~VEngine()
{
}

Cylinder& VEngine::getPistonCylinder()
{
	return pistonCylinder;
}

Prism& VEngine::getConRodPrism()
{
	return conRodPrism;
}

ShaderProgram& VEngine::getShader()
{
	return shader;
}

Cylinder& VEngine::getCrankShaftCylinder()
{
	return crankShaftCylinder;
}

Cylinder& VEngine::getEllipticCylinder()
{
	return ellipticCylinder;
}
