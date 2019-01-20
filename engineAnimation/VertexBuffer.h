#pragma once
#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(GLsizeiptr size, const GLvoid *data, GLenum usage);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
	void set(GLsizeiptr size, const GLvoid *data, GLenum usage) const;

private:
	GLuint bufferId;
};