#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <exception>
#include "shprogram.h"


class TextureMgr
{
public:
	void addTexture(const char* fileName);
	TextureMgr(GLuint currentTextures);
	~TextureMgr();

private:
	GLuint currentTextures;
};

