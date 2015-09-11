#include "Shader.h"

Shader::Shader(char* vertexPath, char* fragmentPath)
{
	this->vertexPath = vertexPath;
	this->fragmentPath = fragmentPath;
}

Shader::~Shader()
{
}

//Compile the shader files passed to the constructor
GLuint Shader::compileShaders() {
	//Strings for shader programs
	std::string vertexShader = "";
	std::string fragmentShader = "";
	std::string line = "";

	//Fstream for vertex shader
	std::fstream vertexStream(getVertexPath());
	if (vertexStream.is_open()) {
		while (std::getline(vertexStream, line)) {
			vertexShader += line + "\n";
		}
		vertexStream.close();
	}
	else {
		fprintf(stderr, "Could not open the vertex shader file");
		return false;
	}

	//Fstream for fragment shader
	std::fstream fragmentStream(getFragmentPath());
	if (fragmentStream.is_open()) {
		while (std::getline(fragmentStream, line)) {
			fragmentShader += line + "\n";
		}
		fragmentStream.close();
	}
	else {
		fprintf(stderr, "Could not open the vertex shader file");
		return false;
	}

	GLint result = GL_FALSE;
	int shaderLogLength;

	//Compile the vertex shader
	char const * vertexSourcePointer = vertexShader.c_str();
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	//Check if the shader compiled successfully
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &shaderLogLength);
	if (shaderLogLength > 0) {
		std::vector<char> shaderErrorMessage(shaderLogLength + 1);
		glGetShaderInfoLog(vertexShaderID, shaderLogLength, NULL, &shaderErrorMessage[0]);
		printf("%s\n", &shaderErrorMessage[0]);
	}

	//Compile the fragment shader
	char const * fragmentSourcePointer = fragmentShader.c_str();
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	//Check if the shader compiled successfully
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &shaderLogLength);
	if (shaderLogLength > 0) {
		std::vector<char> shaderErrorMessage(shaderLogLength + 1);
		glGetShaderInfoLog(fragmentShaderID, shaderLogLength, NULL, &shaderErrorMessage[0]);
		printf("%s\n", &shaderErrorMessage[0]);
	}

	//Compile the program
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	//Check the program compile status
	int programLogLength;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &programLogLength);
	if (programLogLength > 0) {
		std::vector<char> programErrorMessage(programLogLength + 1);
		glGetProgramInfoLog(programID, programLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}

	//Delete the shaders
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}

//Returns the vertex shader path
char* Shader::getVertexPath() {
	return this->vertexPath;
}

//Returns the fragment shader path
char* Shader::getFragmentPath() {
	return this->fragmentPath;
}

//Load the shader programs statically
GLuint Shader::loadShaders(char* vertexPath, char* fragmentPath) {
	//Strings for shader programs
	std::string vertexShader = "";
	std::string fragmentShader = "";
	std::string line = "";

	//Fstream for vertex shader
	std::fstream vertexStream(vertexPath);
	if (vertexStream.is_open()) {
		while (std::getline(vertexStream, line)) {
			vertexShader += line + "\n";
		}
		vertexStream.close();
	}
	else {
		fprintf(stderr, "Could not open the vertex shader file");
		return false;
	}

	//Fstream for fragment shader
	std::fstream fragmentStream(fragmentPath);
	if (fragmentStream.is_open()) {
		while (std::getline(fragmentStream, line)) {
			fragmentShader += line + "\n";
		}
		fragmentStream.close();
	}
	else {
		fprintf(stderr, "Could not open the vertex shader file");
		return false;
	}

	GLint result = GL_FALSE;
	int shaderLogLength;

	//Compile the vertex shader
	char const * vertexSourcePointer = vertexShader.c_str();
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	//Check if the shader compiled successfully
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &shaderLogLength);
	if (shaderLogLength > 0) {
		std::vector<char> shaderErrorMessage(shaderLogLength + 1);
		glGetShaderInfoLog(vertexShaderID, shaderLogLength, NULL, &shaderErrorMessage[0]);
		printf("%s\n", &shaderErrorMessage[0]);
	}

	//Compile the fragment shader
	char const * fragmentSourcePointer = fragmentShader.c_str();
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	//Check if the shader compiled successfully
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &shaderLogLength);
	if (shaderLogLength > 0) {
		std::vector<char> shaderErrorMessage(shaderLogLength + 1);
		glGetShaderInfoLog(fragmentShaderID, shaderLogLength, NULL, &shaderErrorMessage[0]);
		printf("%s\n", &shaderErrorMessage[0]);
	}

	//Compile the program
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	//Check the program compile status
	int programLogLength;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &programLogLength);
	if (programLogLength > 0) {
		std::vector<char> programErrorMessage(programLogLength + 1);
		glGetProgramInfoLog(programID, programLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}

	//Delete the shaders
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}