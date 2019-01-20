#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &bufferId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &bufferId);
}

void VertexArray::bind() const
{
	glBindVertexArray(bufferId);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::associateVertexBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout)
{
	bind();
	vbo.bind();

	const vector<LayoutElement> &elements = layout.getElements();
	GLuint pointer = 0;

	for (GLuint i = 0; i < elements.size(); ++i) {
		const LayoutElement &el = elements[i];
		glVertexAttribPointer(i, el.size, el.type, el.normalized, layout.getStride(),
			(const GLvoid*)pointer);
		glEnableVertexAttribArray(i);
		pointer += el.sizeOfLayoutElement;
	}

	vbo.unbind();
	unbind();
}
