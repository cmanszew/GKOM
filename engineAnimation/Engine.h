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
	const vector<Piston>& getPistons() const;
	const vector<ConnectingRod>& getConRods() const;
	virtual Cylinder& getPistonCylinder() = 0;
	virtual Prism& getConRodPrism() = 0;
	virtual Cylinder& getCrankShaftCylinder() = 0;
	virtual Cylinder& getEllipticCylinder() = 0;
	CrankShaft& getCrankShaft();

	virtual ShaderProgram& getShader() = 0;
	void setAngle(GLfloat angle);
	GLfloat getAngle();

protected:
	vector<Piston> pistons;
	vector<ConnectingRod> conRods;
	CrankShaft crankShaft;
	vector<GLfloat> offsets;
	   	  
	GLfloat angle;
};