#pragma once
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

class Cylinder
{
public:
	Cylinder();
	Cylinder(GLfloat heigth, GLfloat radius);
	void set(GLfloat heigth, GLfloat radius);
	const VertexArray& getVao() const;
	const IndexBuffer& getBaseIbo() const;
	const IndexBuffer& getSideIbo() const;

private:
	//glm::mat4 modelMatrix;
	void genVertices(vector<GLfloat> &vertices, GLfloat heigth, GLfloat radius);
	void genBaseIndices(vector<GLuint> &indices, GLuint cnt);
	void genSideIndices(vector<GLuint> &indices, GLuint cnt);
	VertexBuffer vbo;
	VertexArray vao;
	IndexBuffer sideIbo;
	IndexBuffer baseIbo;
};