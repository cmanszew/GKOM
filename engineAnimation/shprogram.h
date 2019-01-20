#pragma once
#include <string>
#include <glm/glm.hpp>
using namespace std;

class ShaderProgram
{
public:
	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use() const;
	void useStop() const;
	GLuint getProgramId() const;
	void setUniform4f(const GLchar *name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void setUniformMatrix4fv(const GLchar *name, const glm::mat4 &matrix);

private:
	GLuint programId;
	string readShaderCode(const GLchar* shaderPath);
	GLuint compileShader(const GLchar* shaderCode, GLenum shaderType);
	GLint getUniformLocation(const GLchar *name) const;
};