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
	TextureMgr();
	TextureMgr(const char* fname);
	~TextureMgr();
};

