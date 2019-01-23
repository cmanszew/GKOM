#pragma once
#include <glm/glm.hpp>
#include <cmath>
#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "shprogram.h"
#include "Cylinder.h"
#include "Piston.h"
#include "Prism.h"
#include "ConnectingRod.h"
#include "CrankShaft.h"
#include "Engine.h"
#include "EngineConstants.h"
#include "Ground.h"

class Renderer
{
public:
	void drawTriangles(const VertexArray &vao, const IndexBuffer &ibo, const ShaderProgram &theProgram) const;
	void drawTriangleStrip(const VertexArray &vao, const IndexBuffer &ibo, const ShaderProgram &theProgram) const;
	void drawCylinder(Cylinder &cylinder);
	void drawPrism(Prism &prism);
	void drawPistons(Engine &engine, glm::mat4 viewProjection);
	void drawConnectingRods(Engine &engine, glm::mat4 viewProjection);
	void drawGround(Ground & ground, glm::mat4 viewProjection);
	void drawCrankShaft(Engine &engine, glm::mat4 viewProjection);
	void clear(GLfloat r = 0.1f, GLfloat g = 0.2f, GLfloat b = 0.3f, GLfloat a = 1.0f) const;
};