#pragma once
#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <vector>

#include "Cylinder.h"
#include "CylinderTextured.h"
#include "Prism.h"
#include "shprogram.h"
#include "Piston.h"
#include "ConnectingRod.h"
#include "CrankShaft.h"
#include "EngineConstants.h"

using namespace std;

class Engine
{
public:
	Engine();
	Cylinder& getPistonCylinder();
	const vector<Piston>& getPistons() const;
	Prism& getConRodPrism();
	const vector<ConnectingRod>& getConRods() const;
	Cylinder& getCrankShaftCylinder();
	Cylinder& getEllipticCylinder();
	CrankShaft& getCrankShaft();

	ShaderProgram& getShader();
	void setAngle(GLfloat angle);
	GLfloat getAngle();

private:
	vector<GLfloat> offsets;

	CylinderTextured pistonCylinder;
	vector<Piston> pistons;

	Prism conRodPrism;
	vector<ConnectingRod> conRods;

	CylinderTextured crankShaftCylinder;
	CylinderTextured ellipticCylinder;
	CrankShaft crankShaft;

	ShaderProgram shader;

	GLfloat angle;
};