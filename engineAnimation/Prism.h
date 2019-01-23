#pragma once
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

class Prism
{
public:
	Prism(GLfloat length = 0.8, GLfloat thickness = 0.1f, GLfloat topW = 0.1f, GLfloat bottomW = 0.2f);
	virtual void set(GLfloat lenght, GLfloat thickness, GLfloat topW, GLfloat bottomW);
	const VertexArray& getVao() const;
	const IndexBuffer& getBaseIbo() const;
	const IndexBuffer& getSideIbo() const;

protected:
	virtual void genVertices(vector<GLfloat> &vertices, GLfloat thickness, GLfloat length,
		GLfloat topW, GLfloat bottomW);
	virtual void genBaseIndices(vector<GLuint> &indices);
	virtual void genSideIndices(vector<GLuint> &indices);
	VertexBuffer vbo;
	VertexArray vao;
	IndexBuffer baseIbo;
	IndexBuffer sideIbo;
};