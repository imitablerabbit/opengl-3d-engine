//Class includes
#include "Model.h"

//Library includes
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

//Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#pragma once
class Loader
{
	public:
		Loader();
		~Loader();
		Model loadToVao(GLfloat[], int, int);
		Model loadToVao(std::vector<glm::vec3>);
		GLuint createVao();
		GLuint storeData(int, GLfloat[], int);
		void bindVao(GLuint);
		void unbindVao();
};

