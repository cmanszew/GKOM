#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "shprogram.h"

//public
ShaderProgram::ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// prepare vertex and fragment shaders
	string vertexCode = readShaderCode(vertexPath);
	GLuint vertexId = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);

	string fragmentCode = readShaderCode(fragmentPath);
	GLuint fragmentId = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

	// link shader program
	programId = glCreateProgram();
	glAttachShader(programId, vertexId);
	glAttachShader(programId, fragmentId);
	glLinkProgram(programId);

	// Print linking errors if any
	GLint success;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
		string msg = string("Shader program linking: ") + infoLog;
		throw exception(msg.c_str());
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void ShaderProgram::setUniform1i(const GLchar *name, GLint value)
{
	use();
	glUniform1i(glGetUniformLocation(programId, name), value);
	useStop();
}

void ShaderProgram::use() const
{
	glUseProgram(getProgramId());
}

void ShaderProgram::useStop() const
{
	glUseProgram(0);
}

GLuint ShaderProgram::getProgramId() const
{
	return programId;
}

void ShaderProgram::setUniform4f(const GLchar *name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	use();
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
	useStop();
}

void ShaderProgram::setUniformMatrix4fv(const GLchar *name, const glm::mat4 &matrix)
{
	use();
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	useStop();
}

// private
string ShaderProgram::readShaderCode(const GLchar* shaderPath)
{
	ifstream shaderFile;
	shaderFile.exceptions(ifstream::badbit);

	shaderFile.open(shaderPath);
	stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
	shaderFile.close();
	return shaderStream.str();
}

GLuint ShaderProgram::compileShader(const GLchar* shaderCode, GLenum shaderType)
{
	GLuint shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderCode, NULL);
	glCompileShader(shaderId);

	// Print compile errors if any
	GLint success = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
		string msg = string("Shader compilation: ") + infoLog;
		throw exception(msg.c_str());
	}
	return shaderId;
}

GLint ShaderProgram::getUniformLocation(const GLchar *name) const
{
	return glGetUniformLocation(programId, name);
}
