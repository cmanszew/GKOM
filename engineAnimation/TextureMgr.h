#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <exception>


class TextureMgr
{
public:
	GLuint _texture;
	TextureMgr();
	TextureMgr(const char* fname);
	~TextureMgr();
	GLuint LoadMipmapTexture(GLuint texId, const char* fname);
};

