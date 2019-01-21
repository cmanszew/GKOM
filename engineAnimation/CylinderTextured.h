#pragma once
#include "Cylinder.h"

class CylinderTextured :
	public Cylinder
{
public:
	CylinderTextured();
	CylinderTextured(GLfloat height, GLfloat radiusA, GLfloat radiusB = -1.0f);
	~CylinderTextured();
	virtual void set(GLfloat heigth, GLfloat radiusA, GLfloat radiusB) override;
	virtual void genVertices(vector<GLfloat> &vertices, GLfloat heigth, GLfloat radiusA, GLfloat radiusB) override;
};

