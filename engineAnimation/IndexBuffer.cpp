#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
	: idxCount(0)
{
	glGenBuffers(1, &bufferId);
}

IndexBuffer::IndexBuffer(GLuint count, const GLvoid *data, GLenum usage)
	: idxCount(count)
{
	glGenBuffers(1, &bufferId);
	set(count, data, usage);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &bufferId);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::set(GLuint count, const GLvoid *data, GLenum usage)
{
	idxCount = count;

	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, usage);
	unbind();
}

GLuint IndexBuffer::getIdxCount() const
{
	return idxCount;
}
