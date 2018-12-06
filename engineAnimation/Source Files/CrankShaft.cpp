#include <CrankShaft.h>

//CrankShaft::CrankShaft(GLfloat x, GLfloat spacing, GLuint pistonCnt)
//	: x(x), mainShaft()
//{
//	setMainShaft(x, spacing, pistonCnt);
//}

CrankShaft::CrankShaft(GLfloat x, GLfloat spacing, GLuint pistonCnt, const vector<GLfloat> &offsets)
	: x(x), spacing(spacing), pistonCnt(pistonCnt), offsets(offsets), mainShaft(), rodConnectors()
{
	setMainShaft();
}

void CrankShaft::setAngle(GLfloat angle)
{
	this->angle = angle;
	setMainShaft();
	setRodConnectors();
}

GLfloat CrankShaft::getAngle()
{
	return angle;
}

const vector<glm::mat4> CrankShaft::getMainShaft()
{
	return mainShaft;
}

const vector<glm::mat4> CrankShaft::getRodConnectors()
{
	return rodConnectors;
}

const vector<GLfloat>& CrankShaft::getOffset()
{
	return offsets;
}

void CrankShaft::setMainShaft()
{
	glm::mat4 rot = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 trans, rot2;

	mainShaft.clear();
	
	for (GLuint i = 0; i <= pistonCnt; ++i) {
		trans = glm::translate(glm::mat4(), glm::vec3(x + (GLfloat)i * spacing, 0.0f, 0.0f));
		rot2 = glm::rotate(glm::mat4(), -angle, glm::vec3(1.0f, 0.0f, 0.0f));
		mainShaft.push_back(rot2 * trans * rot);
	}
}

void CrankShaft::setRodConnectors()
{
	glm::mat4 rot = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 trans, rot2;

	rodConnectors.clear();

	for (GLuint i = 0; i < pistonCnt; ++i) {
		trans = glm::translate(glm::mat4(), glm::vec3(x + (GLfloat)i * spacing + 0.15f, 0.0f, 0.12f)); //TODO - sort those magic nubers out!!!!
		//trans = glm::translate(glm::mat4(), glm::vec3(x + (GLfloat)i * spacing + 0.15f, 0.0f, 0.145f)); //TODO - sort those magic nubers out!!!!
		rot2 = glm::rotate(glm::mat4(), -angle - offsets[i], glm::vec3(1.0f, 0.0f, 0.0f));
		rodConnectors.push_back(rot2 * trans * rot);

		trans = glm::translate(glm::mat4(), glm::vec3(x + (GLfloat)i * spacing + 0.45f, 0.0f, 0.12f)); //TODO - sort those magic nubers out!!!!
		//trans = glm::translate(glm::mat4(), glm::vec3(x + (GLfloat)i * spacing + 0.45f, 0.0f, 0.145f)); //TODO - sort those magic nubers out!!!!
		rot2 = glm::rotate(glm::mat4(), -angle - offsets[i], glm::vec3(1.0f, 0.0f, 0.0f));
		rodConnectors.push_back(rot2 * trans * rot);
	}
}