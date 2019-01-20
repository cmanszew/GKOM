#pragma once
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <exception>
#include <gl/glew.h>

class TextureMgr
{
public:
	TextureMgr();
	~TextureMgr();
	GLuint LoadMipmapTexture(GLuint texId, const char* fname);
};

