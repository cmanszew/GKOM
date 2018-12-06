#include "Renderer.h"

void Renderer::drawTriangles(const VertexArray &vao, const IndexBuffer &ibo, const ShaderProgram &theProgram) const
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

void Renderer::drawPrism(const Prism &prism, ShaderProgram &theProgram)
{
	theProgram.setUniform4f("uColor", 0.76f, 0.76f, 0.76f, 1.0f);
	drawTriangles(prism.getVao(), prism.getSideIbo(), theProgram);
	theProgram.setUniform4f("uColor", 0.68f, 0.68f, 0.68f, 1.0f);
	drawTriangles(prism.getVao(), prism.getBaseIbo(), theProgram);
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

void Renderer::drawConnectingRod(ConnectingRod &conRod, Prism &prism, ShaderProgram &theProgram, glm::mat4 viewProjection, GLfloat crankRad, GLfloat conRodLen)
{
	const double crankPinY = crankRad * sin(conRod.getAngle() + conRod.getOffset());
	const double crankPinZ = crankRad * cos(conRod.getAngle() + conRod.getOffset());
	glm::mat4 mvp;

	conRod.setY(GLfloat(crankPinY + sqrt(pow(conRodLen, 2) - pow(crankPinZ, 2)) - 0.05f)); //TODO 0.05f == crankPinRad
	conRod.setTilt(GLfloat(-asin(crankPinZ / conRodLen)));
	mvp = viewProjection * conRod.getModelMatrix();
	theProgram.setUniformMatrix4fv("uTransform", mvp);
	drawPrism(prism, theProgram);
}

void Renderer::drawCrankShaft(CrankShaft &crankShaft, Cylinder &cylinder, Cylinder &cylinder2, ShaderProgram &theProgram, glm::mat4 viewProjection)
{
	vector<glm::mat4> vec = crankShaft.getMainShaft();
	vector<glm::mat4> vec2 = crankShaft.getRodConnectors();
	glm::mat4 mvp;

	for (unsigned int i = 0; i < vec.size(); ++i) {
		mvp = viewProjection * vec[i];
		theProgram.setUniformMatrix4fv("uTransform", mvp);
		drawCylinder(cylinder, theProgram);
	}

	for (unsigned int i = 0; i < vec2.size(); ++i) {
		mvp = viewProjection * vec2[i];
		theProgram.setUniformMatrix4fv("uTransform", mvp);
		drawCylinder(cylinder2, theProgram);
	}
}

void Renderer::clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}