#pragma once
#include "PrismTextured.h"
#include "shprogram.h"

class Ground
{
public:
	Ground(GLfloat height = 0.1f, GLfloat width = 50.0f, GLfloat length = 50.0f);
	ShaderProgram& getShader();
	PrismTextured& getGroundPrism();

private:
	PrismTextured groundPrism;
	ShaderProgram shader;
};