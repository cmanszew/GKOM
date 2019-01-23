#pragma once
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "shprogram.h"

using namespace std;

class Cylinder
{
public:
	Cylinder();
	Cylinder(string vertexPath, string fragmentPath);
	Cylinder(GLfloat height, GLfloat radiusA, GLfloat radiusB = -1.0f);
	virtual void set(GLfloat heigth, GLfloat radiusA, GLfloat radiusB = -1.0f);
	const VertexArray& getVao() const;
	const IndexBuffer& getBaseIbo() const;
	const IndexBuffer& getSideIbo() const;
	virtual ShaderProgram& getShader() { return shader; }
	const int angle_inc = 5;

protected:
	virtual void genVertices(vector<GLfloat> &vertices, GLfloat heigth, GLfloat radiusA, GLfloat radiusB = -1.0f);
	virtual void genBaseIndices(vector<GLuint> &indices, GLuint cnt);
	void genSideIndices(vector<GLuint> &indices, GLuint cnt);
	VertexBuffer vbo;
	VertexArray vao;
	IndexBuffer sideIbo;
	IndexBuffer baseIbo;
	ShaderProgram shader;
};