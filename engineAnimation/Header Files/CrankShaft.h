#pragma once
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Cylinder.h"

using namespace std;

class CrankShaft
{
public:
	CrankShaft(GLfloat x, GLfloat spacing, GLuint pistonCnt);
	CrankShaft(GLfloat x, GLfloat spacing, GLuint pistonCnt, const vector<GLfloat> &offsets);
	void setAngle(GLfloat angle);
	GLfloat getAngle();
	const vector<glm::mat4> getMainShaft();
	const vector<glm::mat4> getRodConnectors();
	const vector<GLfloat>& getOffset();
	//GLfloat getX();

private:
	void setMainShaft();
	void setRodConnectors();
	vector<glm::mat4> mainShaft;
	vector<glm::mat4> rodConnectors;
	
	GLfloat x;
	vector<GLfloat> offsets;
	GLfloat angle;
	GLfloat spacing;
	GLuint pistonCnt;
};