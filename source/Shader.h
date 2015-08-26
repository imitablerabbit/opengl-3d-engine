#ifndef SHADER_H
#define SHADER_H

//Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>

//openGL includes
#include <glew.h>

class Shader
{
	public:
		Shader(char*, char*);
		~Shader();
		GLuint compileShaders();
		char* getVertexPath();
		char* getFragmentPath();
		static GLuint loadShaders(char*, char*);

	private:
		char* vertexPath;
		char* fragmentPath;
};

#endif
