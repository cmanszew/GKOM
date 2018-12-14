#pragma once
#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <vector>

#include "Cylinder.h"
#include "Prism.h"
#include "shprogram.h"
#include "Piston.h"
#include "ConnectingRod.h"
#include "CrankShaft.h"

using namespace std;

class Engine
{
public:
	Engine();
	const Cylinder& getPistonCylinder() const;
	const vector<Piston>& getPistons() const;
	const Prism& getConRodPrism() const;
	const vector<ConnectingRod>& getConRods() const;
	const Cylinder& getCrankShaftCylinder() const;
	const Cylinder& getEllipticCylinder() const;
	CrankShaft& getCrankShaft();

	ShaderProgram& getShader();
	void setAngle(GLfloat angle);
	GLfloat getAngle();

private:
	vector<GLfloat> offsets;

	Cylinder pistonCylinder;
	vector<Piston> pistons;

	Prism conRodPrism;
	vector<ConnectingRod> conRods;

	Cylinder crankShaftCylinder;
	Cylinder ellipticCylinder;
	CrankShaft crankShaft;

	ShaderProgram shader;

	GLfloat angle;

public:
	static const GLfloat cylBore;
	static const GLfloat pistonStroke;
	static const GLfloat pistonHeight;
	static const GLfloat conRodLen;

	static const GLfloat conRodThck;
	static const GLfloat crankPinRad;
	static const GLfloat crankShaftRad;

	static const GLfloat cylSpacing;
	static const GLfloat piston1x;
	static const GLfloat crankX;
	static const GLfloat crankRad;
	static const GLfloat crankMainShaftComponent;
};