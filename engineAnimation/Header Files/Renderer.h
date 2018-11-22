#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "shprogram.h"

class Renderer
{
public:
	void drawTriangles(const VertexArray &vao, const IndexBuffer &ibo, const ShaderProgram &theProgram) const;
	void drawTriangleStrip(const VertexArray &vao, const IndexBuffer &ibo, const ShaderProgram &theProgram) const;
	void clear(GLfloat r = 0.1f, GLfloat g = 0.2f, GLfloat b = 0.3f, GLfloat a = 1.0f) const;
};