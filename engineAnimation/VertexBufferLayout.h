#pragma once
#include <vector>
#include <GL/glew.h>

using namespace std;

struct LayoutElement
{
	GLuint size;
	GLenum type;
	GLboolean normalized;
	GLuint sizeOfLayoutElement;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	~VertexBufferLayout();
	void pushGLfloat(GLuint size, GLboolean normalized = GL_FALSE);
	const vector<LayoutElement>& getElements() const;
	GLsizei getStride() const;

private:
	vector<LayoutElement> elements;
	GLsizei stride;
};