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
	void set(GLfloat lenght, GLfloat thickness, GLfloat topW, GLfloat bottomW);
	const VertexArray& getVao() const;
	const IndexBuffer& getIbo() const;

private:
	void genVertices(vector<GLfloat> &vertices, GLfloat thickness, GLfloat length,
		GLfloat topW, GLfloat bottomW);
	void genIndices(vector<GLuint> &indices);
	VertexBuffer vbo;
	VertexArray vao;
	IndexBuffer ibo;
};