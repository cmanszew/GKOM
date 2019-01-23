#pragma once
#include "Prism.h"

class PrismTextured :
	public Prism
{
public:
	PrismTextured(GLfloat length = 0.8, GLfloat thickness = 0.1f, GLfloat topW = 0.1f, GLfloat bottomW = 0.2f);
	~PrismTextured();
	virtual void set(GLfloat lenght, GLfloat thickness, GLfloat topW, GLfloat bottomW) override;

protected:
	virtual void genVertices(vector<GLfloat> &vertices, GLfloat thickness, GLfloat length,
		GLfloat topW, GLfloat bottomW) override;
	virtual void genBaseIndices(vector<GLuint> &indices) override;
	virtual void genSideIndices(vector<GLuint> &indices) override;
};
