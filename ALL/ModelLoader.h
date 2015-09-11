#ifndef MODELLOADER_H
#define MODELLOADER_H

//Class includes
#include "Model.h"
#include "TextureLoader.h"
#include "StringUtils.h"

//Library includes
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

//Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class ModelLoader
{
	public:
		ModelLoader();
		~ModelLoader();

		//Load a model from an array of vertices
		Model loadToVao(GLfloat[], const int, const int, const float, const float, const float, glm::vec3, GLfloat[], int);
		Model loadToVao(GLfloat[], const int, const int, const float, glm::vec3, GLfloat[], int);
		Model loadToVao(std::vector<glm::vec3>, const float, const float, const float, glm::vec3, std::vector<glm::vec3>);
		Model loadToVao(std::vector<glm::vec3>, const float, const float, const float, glm::vec3, glm::vec3);
		Model loadToVao(std::vector<glm::vec3>, const float, glm::vec3, std::vector<glm::vec3>);
		Model loadToVao(std::vector<glm::vec3>, const float, glm::vec3, glm::vec3);
		Model loadToVao(std::vector<glm::vec3>, glm::vec3, glm::vec3);
		Model loadToVao(std::vector<glm::vec3>, glm::vec3);

		//Load a standard model using one of the const ints defined in this class
		Model loadToVao(const int, float, float, float, glm::vec3, std::vector<glm::vec3>);
		Model loadToVao(const int, float, float, float, glm::vec3, glm::vec3);
		Model loadToVao(const int, float, glm::vec3, std::vector<glm::vec3>);
		Model loadToVao(const int, float, glm::vec3, glm::vec3);
		Model loadToVao(const int, glm::vec3, glm::vec3);
		Model loadToVao(const int, glm::vec3);
		Model loadToVao(const int);

		//Load a model from an OBJ file
		Model loadToVao_OBJ(const char*, float, float, float, glm::vec3, std::vector<glm::vec3>);
		Model loadToVao_OBJ(const char*, float, float, float, glm::vec3, glm::vec3);
		Model loadToVao_OBJ(const char*, float, glm::vec3, std::vector<glm::vec3>);
		Model loadToVao_OBJ(const char*, float, glm::vec3, glm::vec3);
		Model loadToVao_OBJ(const char*, glm::vec3, glm::vec3);
		Model loadToVao_OBJ(const char*, glm::vec3);
		Model loadToVao_OBJ(const char*);

		//Load a TexturedModel from an OBJ file and a texture file
		Model loadToVao_OBJ_Textured(const char*, const char*, float, float, float, glm::vec3, std::vector<glm::vec3>);
		Model loadToVao_OBJ_Textured(const char*, const char*, float, float, float, glm::vec3, glm::vec3);
		Model loadToVao_OBJ_Textured(const char*, const char*, float, glm::vec3, std::vector<glm::vec3>);
		Model loadToVao_OBJ_Textured(const char*, const char*, float, glm::vec3, glm::vec3);
		Model loadToVao_OBJ_Textured(const char*, const char*, glm::vec3, glm::vec3);
		Model loadToVao_OBJ_Textured(const char*, const char*, glm::vec3);
		Model loadToVao_OBJ_Textured(const char*, const char*);

		//The OBJ parser
		bool loadOBJ(const char*, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&, const unsigned int);

		//Functions to get the model data from the standard models
		std::vector<glm::vec3> getModelData(const int);
		std::vector<glm::vec3> loadModelFromFile(const char*);

		//Data binder functions
		GLuint createVao();
		GLuint storeData(int, GLfloat[], int);
		void bindVao(GLuint);
		void unbindVao();

		//Standard models that can be used
		static const int MODEL_CUBE = 1;
		static const int MODEL_SQUARE = 2;
		static const int MODEL_TRIANGLE = 3;

		//OBJ loader flags
		static const unsigned int NORMAL_LOADING = 1;
		static const unsigned int UV_INVERT_Y = 2;
};

#endif