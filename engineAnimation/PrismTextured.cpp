#include "PrismTextured.h"

PrismTextured::PrismTextured(GLfloat length, GLfloat thickness, GLfloat topW, GLfloat bottomW)
	: Prism("groundShader.vert", "groundShader.frag")
{
	set(length, thickness, topW, bottomW);
}

PrismTextured::~PrismTextured()
{
}

void PrismTextured::set(GLfloat length = 0.8, GLfloat thickness = 0.1f, GLfloat topW = 0.1f, GLfloat bottomW = 0.2f)
{
	vector<GLfloat> vertices;
	vector<GLuint> indices;
	vector<GLuint> baseIndices, sideIndices;
	VertexBufferLayout vbl;

	genVertices(vertices, thickness, length, topW, bottomW);
	vbo.set(sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	vbl.pushGLfloat(3); //coordinates 
	vbl.pushGLfloat(2); //coordinates 
	vao.associateVertexBuffer(vbo, vbl);

	genBaseIndices(baseIndices);
	baseIbo.set(baseIndices.size(), &baseIndices[0], GL_STATIC_DRAW);

	genSideIndices(sideIndices);
	sideIbo.set(sideIndices.size(), &sideIndices[0], GL_STATIC_DRAW);

}

void PrismTextured::genBaseIndices(vector<GLuint> &indices)
{
	indices = {
	1, 2, 6,
	6, 5, 1,
	3, 0, 4,
	4, 7, 3,
	};
}

void PrismTextured::genSideIndices(vector<GLuint> &indices)
{
	indices = {
	0, 1, 2,
	2, 3, 0,
	4, 5, 6,
	6, 7, 4,

	0, 1, 5,
	5, 4, 0,
	2, 3, 7,
	7, 6, 2,
	};
}

void PrismTextured::genVertices(vector<GLfloat> &vertices, GLfloat thickness, GLfloat length,
	GLfloat topW, GLfloat bottomW)
{
	vertices = {
		-thickness / 2, -length, bottomW / 2, 0.0f, 0.0f,
		thickness / 2, -length, bottomW / 2, 0.0f, 0.0f,
		thickness / 2, -length, -bottomW / 2, 0.0f, 0.0f,
		-thickness / 2, -length, -bottomW / 2, 0.0f, 0.0f,

		-thickness / 2, 0, topW / 2, 0.0f, 10.0f,
		thickness / 2, 0, topW / 2, 10.0f, 10.0f,
		thickness / 2, 0, -topW / 2, 10.0f, 0.0f,
		-thickness / 2, 0, -topW / 2, 0.0f, 0.0f
	};
}

