#pragma once
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	/* One must bind the target VertexBuffer object and VertexArray object,
	 * before an addLayout function call. */
	void associateVertexBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout);

private:
	GLuint bufferId;
};