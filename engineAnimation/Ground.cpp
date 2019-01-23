#include "Ground.h"

Ground::Ground(GLfloat height, GLfloat width, GLfloat length)
	:groundPrism(height, width, length, length),
	shader("groundShader.vert", "groundShader.frag")
{}

ShaderProgram& Ground::getShader()
{
	return shader;
}

 PrismTextured& Ground::getGroundPrism()
{
	return groundPrism;
}