#include "TextureMgr.h"

TextureMgr::TextureMgr(GLuint currentTexturesCount = 0):
	currentTextures(currentTexturesCount)
{
}

void TextureMgr::addTexture(const char* fileName, int samplingType) 
{
	GLuint textures;
	glGenTextures(1, &textures);

	int width, height;
	unsigned char* image;

	glActiveTexture(GL_TEXTURE0 + currentTextures);
	glBindTexture(GL_TEXTURE_2D, textures);
	image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, samplingType);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, samplingType);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	currentTextures += 1;
}


TextureMgr::~TextureMgr()
{
}
