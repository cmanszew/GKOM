#pragma once
#include "Prism.h"
#include "shprogram.h"

class Ground
{
public:
	Ground(GLfloat height = 0.1f, GLfloat width = 50.0f, GLfloat length = 50.0f);
	ShaderProgram& getShader();
	const Prism& getGroundPrism() const;

private:
	Prism groundPrism;
	ShaderProgram shader;
};