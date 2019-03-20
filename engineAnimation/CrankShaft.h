#pragma once
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Cylinder.h"
#include "EngineConstants.h"

using namespace std;

class CrankShaft
{
public:
	CrankShaft();
	CrankShaft(GLuint pistonCnt, const vector<GLfloat> &offsets);
	void setup(GLuint pistonCnt, const vector<GLfloat> &offsets, GLfloat rodsPerConnector = 1.0f);
	void setAngle(GLfloat angle);
	void setMainShaft();
	void setRodConnectors();
	GLfloat getAngle();
	const vector<glm::mat4> getMainShaft();
	const vector<glm::mat4> getRodConnectors();
	const vector<GLfloat>& getOffset();

private:
	vector<glm::mat4> mainShaft;
	vector<glm::mat4> rodConnectors;
	
	vector<GLfloat> offsets;
	GLfloat angle;
	GLuint pistonCnt;
	GLfloat rodsPerConnector;
};