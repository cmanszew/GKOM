#pragma once
#include "Engine.h"
class VEngine :
	public Engine
{
public:
	VEngine(GLfloat vAngle = glm::radians(90.0f));
	~VEngine();
	virtual Cylinder& getPistonCylinder() override;
	virtual Prism& getConRodPrism() override;
	virtual Cylinder& getCrankShaftCylinder() override;
	virtual Cylinder& getEllipticCylinder() override;
	virtual ShaderProgram& getShader() override;

protected:
	CylinderTextured pistonCylinder;
	Prism conRodPrism;
	CylinderTextured crankShaftCylinder;
	CylinderTextured ellipticCylinder;

	ShaderProgram shader;

	GLfloat vAngle;
};

