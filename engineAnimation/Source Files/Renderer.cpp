#include "Renderer.h"

void Renderer::drawTriangles(const VertexArray &vao, const IndexBuffer & ibo, const ShaderProgram & theProgram) const
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

void Renderer::drawCylinder(const Cylinder &cylinder, ShaderProgram &theProgram)
{
	theProgram.setUniform4f("uColor", 0.82f, 0.82f, 0.85f, 1.0f);
	drawTriangles(cylinder.getVao(), cylinder.getBaseIbo(), theProgram);
	theProgram.setUniform4f("uColor", 0.92f, 0.92f, 0.95f, 1.0f);
	drawTriangleStrip(cylinder.getVao(), cylinder.getSideIbo(), theProgram);
}

void Renderer::drawPiston(Piston &piston, Cylinder &cylinder, ShaderProgram &theProgram, glm::mat4 viewProjection, GLfloat crankRad, GLfloat conRodLen)
{
	const double crankPinY = crankRad * sin(piston.getAngle() + piston.getOffset());
	const double crankPinZ = crankRad * cos(piston.getAngle() + piston.getOffset());
	glm::mat4 mvp;

	piston.setY(GLfloat(crankPinY + sqrt(pow(conRodLen, 2) - pow(crankPinZ, 2))));
	mvp = viewProjection * piston.getModelMatrix();
	theProgram.setUniformMatrix4fv("uTransform", mvp);
	drawCylinder(cylinder, theProgram);
}


void Renderer::clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}