#pragma once
#include "Engine.h"
class inlineEngine :
	public Engine
{
public:
	inlineEngine();
	~inlineEngine();
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
};

