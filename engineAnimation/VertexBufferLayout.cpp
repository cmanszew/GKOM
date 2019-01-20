#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
	: stride(0)
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}

void VertexBufferLayout::pushGLfloat(GLuint size, GLboolean normalized)
{
	elements.push_back({size, GL_FLOAT, normalized, size * sizeof(GLfloat)});
	stride += size * sizeof(GLfloat);
}

const vector<LayoutElement>& VertexBufferLayout::getElements() const
{
	return elements;
}

GLsizei VertexBufferLayout::getStride() const
{
	return stride;
}
