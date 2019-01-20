#include "Cylinder.h"

using namespace std;

Cylinder::Cylinder()
{
}

Cylinder::Cylinder(GLfloat height, GLfloat radiusA, GLfloat radiusB)
{
	set(height, radiusA, radiusB);
}

void Cylinder::set(GLfloat heigth, GLfloat radiusA, GLfloat radiusB)
{
	vector<GLfloat> vertices;
	vector<GLuint> baseIndices, sideIndices;
	VertexBufferLayout vbl;

	genVertices(vertices, heigth, radiusA, radiusB);
	vbo.set(sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	vbl.pushGLfloat(3); // position
	vbl.pushGLfloat(2); // texture
	vao.associateVertexBuffer(vbo, vbl);
	
	genBaseIndices(baseIndices, vertices.size() / 5 - 1);
	baseIbo.set(baseIndices.size(), &baseIndices[0], GL_STATIC_DRAW);

	genSideIndices(sideIndices, vertices.size() / 5 - 2);
	sideIbo.set(sideIndices.size(), &sideIndices[0], GL_STATIC_DRAW);
}

const VertexArray& Cylinder::getVao() const
{
	return vao;
}

const IndexBuffer& Cylinder::getBaseIbo() const
{
	return baseIbo;
}

const IndexBuffer& Cylinder::getSideIbo() const
{
	return sideIbo;
}

void Cylinder::genVertices(vector<GLfloat> &vertices, GLfloat heigth, GLfloat radiusA, GLfloat radiusB)
{
	const int angle_inc = 5;

	radiusB = radiusB < 0.0f ? radiusA : radiusB;

	for (int angle = 0; angle < 360; angle += angle_inc) {
		vertices.push_back(radiusA * (float)cos((double)angle * M_PI / 180.0));
		vertices.push_back(heigth / 2);
		vertices.push_back(radiusB * (float)sin((double)angle * M_PI / 180.0));
		vertices.push_back((float)angle / 360); // texture X interpolate
		vertices.push_back((float)1); // texture Y


		vertices.push_back(radiusA * (float)cos((double)angle * M_PI / 180.0));
		vertices.push_back(-heigth / 2);
		vertices.push_back(radiusB * (float)sin((double)angle * M_PI / 180.0));
		vertices.push_back((float)angle / 360); // texture X interpolate
		vertices.push_back((float)0); // texture Y
	}
	vertices.push_back(0.0f);
	vertices.push_back(heigth / 2);
	vertices.push_back(0.0f);
	vertices.push_back((float)0.5f); // texture X interpolate
	vertices.push_back((float)1.0f); // texture Y

	vertices.push_back(0.0f);
	vertices.push_back(-heigth / 2);
	vertices.push_back(0.0f);
	vertices.push_back((float)0.5f); // texture X interpolate
	vertices.push_back((float)0); // texture Y
}

void Cylinder::genBaseIndices(vector<GLuint> &indices, GLuint cnt)
{
	for (GLuint i = 0; i < cnt - 1; i += 2) {
		indices.push_back(cnt - 1);
		indices.push_back(i);
		indices.push_back((i + 2) % (cnt - 1));
		cout << "Drawing: " << cnt - 1 << " " << i << " " << (i + 2) % (cnt - 1) << endl;
	}

	for (GLuint i = 1; i < cnt; i += 2) {
		indices.push_back(cnt);
		indices.push_back(i);
		indices.push_back((i + 1) % (cnt - 1) + 1);
		cout << "Drawing: " << cnt << " " << i << " " << (i + 2) % cnt << endl;
	}
}

void Cylinder::genSideIndices(vector<GLuint> &indices, GLuint cnt)
{
	for (int i = 0; i < cnt; ++i) {
		indices.push_back(i);
	}
	indices.push_back(0);
	indices.push_back(1);
}

