#include "Prism.h"

Prism::Prism(GLfloat length, GLfloat thickness, GLfloat topW, GLfloat bottomW)
{
	set(length, thickness, topW, bottomW);
}

void Prism::set(GLfloat length = 0.8, GLfloat thickness = 0.1f, GLfloat topW = 0.1f, GLfloat bottomW = 0.2f)
{
	vector<GLfloat> vertices;
	vector<GLuint> indices;
	VertexBufferLayout vbl;

	genVertices(vertices, thickness, length, topW, bottomW);
	vbo.set(sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	
	vbl.pushGLfloat(3);
	vao.associateVertexBuffer(vbo, vbl);
	
	genIndices(indices);
	ibo.set(indices.size(), &indices[0], GL_STATIC_DRAW);
}

const VertexArray& Prism::getVao() const
{
	return vao;
}
const IndexBuffer& Prism::getIbo() const
{
	return ibo;
}

void Prism::genVertices(vector<GLfloat> &vertices, GLfloat thickness, GLfloat length,
	GLfloat topW, GLfloat bottomW)
{
	vertices = {
		-thickness / 2, -length, bottomW / 2,
		thickness / 2, -length, bottomW / 2,
		thickness / 2, -length, -bottomW / 2,
		-thickness / 2, -length, -bottomW / 2,

		-thickness / 2, 0, topW / 2,
		thickness / 2, 0, topW / 2,
		thickness / 2, 0, -topW / 2,
		-thickness / 2, 0, -topW / 2,
	};
}

void Prism::genIndices(vector<GLuint> &indices)
{
	indices = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,

		0, 1, 5,
		5, 4, 0,
		1, 2, 6,
		6, 5, 1,
		2, 3, 7,
		7, 6, 2,
		3, 0, 4,
		4, 7, 3,
	};
}