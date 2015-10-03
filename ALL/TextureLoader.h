#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>

class TextureLoader
{
	public:
		TextureLoader();
		~TextureLoader();

		GLuint loadBMP_custom(const char * imagepath);
		GLuint loadDDS(const char * imagepath);
};

#endif
