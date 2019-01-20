#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &bufferId);
}

VertexBuffer::VertexBuffer(GLsizeiptr size, const GLvoid *data, GLenum usage)
{
	glGenBuffers(1, &bufferId);
	set(size, data, usage);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &bufferId);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::set(GLsizeiptr size, const GLvoid *data, GLenum usage) const
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	unbind();
}