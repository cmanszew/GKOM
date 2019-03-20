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

void Renderer::drawCylinder(Cylinder &cylinder)
{
	auto& shader = cylinder.getShader();
	shader.setUniform4f("uColor", 1.0f, 1.0f, 1.0f, 1.0f);
	drawTriangles(cylinder.getVao(), cylinder.getBaseIbo(), shader);
	shader.setUniform4f("uColor", 1.0f, 1.0f, 1.0f, 1.0f);
	drawTriangleStrip(cylinder.getVao(), cylinder.getSideIbo(), shader);
}

void Renderer::drawPrism(Prism &prism)
{
	auto& shader = prism.getShader();
	shader.setUniform4f("uColor", 0.76f, 0.76f, 0.76f, 1.0f);
	drawTriangles(prism.getVao(), prism.getSideIbo(), shader);
	shader.setUniform4f("uColor", 0.68f, 0.68f, 0.68f, 1.0f);
	drawTriangles(prism.getVao(), prism.getBaseIbo(), shader);
}

void Renderer::drawPistons(Engine &engine, glm::mat4 viewProjection)
{
	glm::mat4 mvp;

	for (auto piston : engine.getPistons()) {
		piston.setPosition(engine.getAngle());
		mvp = viewProjection * piston.getModelMatrix();
		engine.getPistonCylinder().getShader().setUniformMatrix4fv("uTransform", mvp);
		drawCylinder(engine.getPistonCylinder());
	}
}

void Renderer::drawConnectingRods(Engine &engine, glm::mat4 viewProjection)
{
	glm::mat4 mvp;

	for (auto conRod : engine.getConRods()) {
		conRod.setPosition(engine.getAngle());
		mvp = viewProjection * conRod.getModelMatrix();
		engine.getConRodPrism().getShader().setUniformMatrix4fv("uTransform", mvp);
		drawPrism(engine.getConRodPrism());
	}
}

void Renderer::drawCrankShaft(Engine &engine, glm::mat4 viewProjection)
{
	vector<glm::mat4> vec = engine.getCrankShaft().getMainShaft();
	vector<glm::mat4> vec2 = engine.getCrankShaft().getRodConnectors();
	glm::mat4 mvp;

	for (unsigned int i = 0; i < vec.size(); ++i) {
		mvp = viewProjection * vec[i];
		engine.getCrankShaftCylinder().getShader().setUniformMatrix4fv("uTransform", mvp);
		drawCylinder(engine.getCrankShaftCylinder());
	}

	for (unsigned int i = 0; i < vec2.size(); ++i) {
		mvp = viewProjection * vec2[i];
		engine.getEllipticCylinder().getShader().setUniformMatrix4fv("uTransform", mvp);
		drawCylinder(engine.getEllipticCylinder());
	}
}

void Renderer::clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}