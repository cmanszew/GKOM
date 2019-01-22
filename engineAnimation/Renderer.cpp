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
	theProgram.setUniform4f("uColor", 0.87f, 0.87f, 0.92f, 1.0f);
	drawTriangles(cylinder.getVao(), cylinder.getBaseIbo(), theProgram);
	theProgram.setUniform4f("uColor", 1.0f, 1.0f, 1.0f, 1.0f);
	drawTriangleStrip(cylinder.getVao(), cylinder.getSideIbo(), theProgram);
}

void Renderer::drawPrism(const Prism &prism, ShaderProgram &theProgram)
{
	theProgram.setUniform4f("uColor", 0.76f, 0.76f, 0.76f, 1.0f);
	drawTriangles(prism.getVao(), prism.getSideIbo(), theProgram);
	theProgram.setUniform4f("uColor", 0.68f, 0.68f, 0.68f, 1.0f);
	drawTriangles(prism.getVao(), prism.getBaseIbo(), theProgram);
}

void Renderer::drawPistons(Engine &engine, glm::mat4 viewProjection)
{
	double crankPinY, crankPinZ;
	glm::mat4 mvp;

	for (auto piston : engine.getPistons()) {
		crankPinY = EngConst::crankRad * sin(engine.getAngle() + piston.getOffset());
		crankPinZ = EngConst::crankRad * cos(engine.getAngle() + piston.getOffset());
		piston.setY(GLfloat(crankPinY + sqrt(pow(EngConst::conRodLen, 2) - pow(crankPinZ, 2))));
		mvp = viewProjection * piston.getModelMatrix();
		engine.getShader().setUniformMatrix4fv("uTransform", mvp);
		drawCylinder(engine.getPistonCylinder(), engine.getShader());
	}
}

void Renderer::drawConnectingRods(Engine &engine, glm::mat4 viewProjection)
{
	double crankPinY, crankPinZ;
	glm::mat4 mvp;

	for (auto conRod : engine.getConRods()) {
		crankPinY = EngConst::crankRad * sin(engine.getAngle() + conRod.getOffset());
		crankPinZ = EngConst::crankRad * cos(engine.getAngle() + conRod.getOffset());
		conRod.setY(GLfloat(crankPinY + sqrt(pow(EngConst::conRodLen, 2) - pow(crankPinZ, 2)) - EngConst::crankPinRad));
		conRod.setTilt(GLfloat(-asin(crankPinZ / EngConst::conRodLen)));
		mvp = viewProjection * conRod.getModelMatrix();
		engine.getShader().setUniformMatrix4fv("uTransform", mvp);
		drawPrism(engine.getConRodPrism(), engine.getShader());
	}
}

void Renderer::drawCrankShaft(Engine &engine, glm::mat4 viewProjection)
{
	vector<glm::mat4> vec = engine.getCrankShaft().getMainShaft();
	vector<glm::mat4> vec2 = engine.getCrankShaft().getRodConnectors();
	glm::mat4 mvp;

	for (unsigned int i = 0; i < vec.size(); ++i) {
		mvp = viewProjection * vec[i];
		engine.getShader().setUniformMatrix4fv("uTransform", mvp);
		drawCylinder(engine.getCrankShaftCylinder(), engine.getShader());
	}

	for (unsigned int i = 0; i < vec2.size(); ++i) {
		mvp = viewProjection * vec2[i];
		engine.getShader().setUniformMatrix4fv("uTransform", mvp);
		drawCylinder(engine.getEllipticCylinder(), engine.getShader());
	}
}

void Renderer::clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}