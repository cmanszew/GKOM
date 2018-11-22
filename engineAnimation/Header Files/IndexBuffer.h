#pragma once
#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(GLuint count, const GLvoid *data, GLenum usage);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
	void set(GLuint count, const GLvoid *data, GLenum usage);
	GLuint getIdxCount() const;
private:
	GLuint bufferId;
	GLuint idxCount;
};