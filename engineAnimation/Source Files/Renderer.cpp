#include "Renderer.h"

void Renderer::drawTriangles(const VertexArray & vao, const IndexBuffer & ibo, const ShaderProgram & theProgram) const
{
	theProgram.use();
	vao.bind();
	ibo.bind();
	glDrawElements(GL_TRIANGLES, ibo.getIdxCount(), GL_UNSIGNED_INT, nullptr);
	ibo.unbind();
	vao.unbind();
	theProgram.useStop();
}

void Renderer::drawTriangleStrip(const VertexArray &vao, const IndexBuffer &ibo, const ShaderProgram &theProgram) const
{
	theProgram.use();
	vao.bind();
	ibo.bind();
	glDrawElements(GL_TRIANGLE_STRIP, ibo.getIdxCount(), GL_UNSIGNED_INT, nullptr);
	ibo.unbind();
	vao.unbind();
	theProgram.useStop();
}

void Renderer::clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}