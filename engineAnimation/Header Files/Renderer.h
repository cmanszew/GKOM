#pragma once
#include <glm/glm.hpp>
#include <cmath>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "shprogram.h"
#include "Cylinder.h"
#include "Piston.h"
#include "Prism.h"
#include "ConnectingRod.h"

class Renderer
{
public:
	void drawTriangles(const VertexArray &vao, const IndexBuffer &ibo, const ShaderProgram &theProgram) const;
	void drawTriangleStrip(const VertexArray &vao, const IndexBuffer &ibo, const ShaderProgram &theProgram) const;
	void drawCylinder(const Cylinder &cylinder, ShaderProgram &theProgram);
	void drawPiston(Piston &piston, Cylinder &cylinder, ShaderProgram &theProgram, glm::mat4 viewProjection, GLfloat crankRad, GLfloat conRodLen);
	void drawConnectingRod(ConnectingRod &conRod, Prism &prism, ShaderProgram &theProgram, glm::mat4 viewProjection, GLfloat crankRad, GLfloat conRodLen);
	void clear(GLfloat r = 0.1f, GLfloat g = 0.2f, GLfloat b = 0.3f, GLfloat a = 1.0f) const;
};