#include "ModelLoader.h"

ModelLoader::ModelLoader() {
}

ModelLoader::~ModelLoader() {
}

/*
VERTICES MODEL LOADER
*/

//Load the data to a vao
Model ModelLoader::loadToVao(GLfloat vertices[], const int verticesSize, const int vertexCount, const float scaleX,
	const float scaleY, const float scaleZ, glm::vec3 position, GLfloat colors[], int colorSize) {
	GLuint vaoID = createVao();
	bindVao(vaoID);

	GLuint verticesVboID = storeData(0, vertices, verticesSize);
	GLuint colorsVboID = storeData(1, colors, colorSize);

	unbindVao();
	return Model(vaoID, verticesVboID, colorsVboID, vertexCount, scaleX, scaleY, scaleZ, position);
}

//Load the data to a vao
Model ModelLoader::loadToVao(GLfloat vertices[], const int verticesSize, const int vertexCount, const float scale,
	glm::vec3 position, GLfloat colors[], const int colorSize) {
	Model temp = loadToVao(vertices, verticesSize, vertexCount, scale, scale, scale, position, colors, colorSize);
	return temp;
}

//Overloaded function so that the function can take a vector of vertices and a vector of colors as well as different axis scaling
Model ModelLoader::loadToVao(std::vector<glm::vec3> vertices, const float scaleX, const float scaleY, const float scaleZ,
	glm::vec3 position, std::vector<glm::vec3> colors) {
	GLfloat *verticesTemp = &vertices[0].x;
	int verticesSize = vertices.size() * 3 * sizeof(GLfloat);
	int vertexCount = vertices.size();

	GLfloat *colorsTemp = &colors[0].x;
	int colorsSize = colors.size() * 3 * sizeof(GLfloat);

	Model temp = loadToVao(verticesTemp, verticesSize, vertexCount, scaleX, scaleY, scaleZ, position, colorsTemp, colorsSize);
	return temp;
}

//Overloaded function so that the function can take a vector of vertices and a color
Model ModelLoader::loadToVao(std::vector<glm::vec3> vertices, const float scaleX, const float scaleY,
	const float scaleZ, glm::vec3 position, glm::vec3 color) {
	std::vector<glm::vec3> colors = std::vector<glm::vec3>();
	for (int i = 0; i < vertices.size(); i++) {
		colors.insert(colors.end(), color);
	}

	Model temp = loadToVao(vertices, scaleX, scaleY, scaleZ, position, colors);
	return temp;
}

//Overloaded function so that the function can take a vector of vertices and a vector of colors
Model ModelLoader::loadToVao(std::vector<glm::vec3> vertices, float scale, glm::vec3 position,
	std::vector<glm::vec3> colors) {
	Model temp = loadToVao(vertices, scale, scale, scale, position, colors);
	return temp;
}

//Overloaded function so that the function can take a vector of vertices and a color
Model ModelLoader::loadToVao(std::vector<glm::vec3> vertices, float scale, glm::vec3 position,
	glm::vec3 color) {
	Model temp = loadToVao(vertices, scale, scale, scale, position, color);
	return temp;
}

//Overloaded function so that the function can take a vector of vertices and a color
Model ModelLoader::loadToVao(std::vector<glm::vec3> vertices, glm::vec3 position,
	glm::vec3 color) {
	Model temp = loadToVao(vertices, 1.0f, position, color);
	return temp;
}

//Overloaded function so that the function can take a vector of vertices and a color
Model ModelLoader::loadToVao(std::vector<glm::vec3> vertices, glm::vec3 position) {
	Model temp = loadToVao(vertices, 1.0f, position, glm::vec3(1, 0, 0));
	return temp;
}

/*
STANDARD MODELS LOADERS
*/

//Function can take a model type, multiple axis scales, a position and an array of color values
Model ModelLoader::loadToVao(const int modelType, float scaleX, float scaleY, float scaleZ, glm::vec3 position,
	std::vector<glm::vec3> colors)
{
	std::vector<glm::vec3> vertices = getModelData(modelType);

	Model temp = loadToVao(vertices, scaleX, scaleY, scaleZ, position, colors);
	return temp;
}

//Overloaded function so that the function can take a model type, a scale, a position and a color value
Model ModelLoader::loadToVao(const int modelType, float scaleX, float scaleY, float scaleZ, glm::vec3 position,
	glm::vec3 color) {
	std::vector<glm::vec3> vertices = getModelData(modelType);

	std::vector<glm::vec3> colors = std::vector<glm::vec3>();
	for (int i = 0; i < vertices.size(); i++) {
		colors.insert(colors.end(), color);
	}

	Model temp = loadToVao(vertices, scaleX, scaleY, scaleZ, position, colors);
	return temp;
}

//Overloaded function so that the function can take a model type, a scale, a position and an array of color values
Model ModelLoader::loadToVao(const int modelType, float scale, glm::vec3 position,
	std::vector<glm::vec3> colors) {
	Model temp = loadToVao(modelType, scale, scale, scale, position, colors);
	return temp;
}

//Overloaded function so that the function can take a model type, a scale, a position and a color value
Model ModelLoader::loadToVao(const int modelType, float scale, glm::vec3 position, glm::vec3 color) {
	Model temp = loadToVao(modelType, scale, scale, scale, position, color);
	return temp;
}

//Overloaded function so that the function can take a model type, a position and a color value
Model ModelLoader::loadToVao(const int modelType, glm::vec3 position, glm::vec3 color) {
	float scale = 1.0f;

	Model temp = loadToVao(modelType, scale, position, color);
	return temp;
}

//Overloaded function so that the function can take a model type and a position
Model ModelLoader::loadToVao(const int modelType, glm::vec3 position) {
	float scale = 1.0f;
	glm::vec3 color = glm::vec3(1, 0, 0);

	Model temp = loadToVao(modelType, scale, position, color);
	return temp;
}

//Overloaded function so that the function can take a model type
Model ModelLoader::loadToVao(const int modelType) {
	float scale = 1.0f;
	glm::vec3 color = glm::vec3(1, 0, 0);
	glm::vec3 position = glm::vec3(0, 0, 0);

	Model temp = loadToVao(modelType, scale, position, color);
	return temp;
}

/*
OBJ LOADER
*/

//Load the model from an OBJ file: Using a path, mulitple scales, position and array of colours
Model ModelLoader::loadToVao_OBJ(const char* filePath, float scaleX, float scaleY, float scaleZ, glm::vec3 position,
	std::vector<glm::vec3> colors) {
	//Arrays for the information
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	Model model;

	//Load the Model
	if (loadOBJ(filePath, vertices, uvs, normals, UV_INVERT_Y)) {
		model = loadToVao(vertices, scaleX, scaleY, scaleZ, position, colors);

		//Check if the model had uvs and normals
		if (uvs.size() > 0) {
			GLfloat* uvsTemp = &uvs[0].x;
			int uvsSize = uvs.size() * 2 * sizeof(GLfloat);
			model.setUVsVboID(storeData(2, uvsTemp, uvsSize));
		}

		if (normals.size() > 0) {
			GLfloat* normalsTemp = &normals[0].x;
			int normalsSize = normals.size() * 3 * sizeof(GLfloat);
			model.setNormalsVboID(storeData(3, normalsTemp, normalsSize));
		}
	}
	else {
		fprintf(stderr, "Could not load the model, using a standard model instead.");
		model = Model();
	}

	return model;
}

//Load the model from an OBJ file: Using a path, scale, position and a color
Model ModelLoader::loadToVao_OBJ(const char* filePath, float scaleX, float scaleY, float scaleZ, glm::vec3 position,
	glm::vec3 color) {
	//Arrays for the information
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	Model model;

	//Load the Model
	if (loadOBJ(filePath, vertices, uvs, normals, UV_INVERT_Y)) {
		model = loadToVao(vertices, scaleX, scaleY, scaleZ, position, color);

		//Check if the model had uvs and normals
		if (uvs.size() > 0) {
			GLfloat* uvsTemp = &uvs[0].x;
			int uvsSize = uvs.size() * 2 * sizeof(GLfloat);
			model.setUVsVboID(storeData(2, uvsTemp, uvsSize));
		}

		if (normals.size() > 0) {
			GLfloat* normalsTemp = &normals[0].x;
			int normalsSize = normals.size() * 3 * sizeof(GLfloat);
			model.setNormalsVboID(storeData(3, normalsTemp, normalsSize));
		}
	}
	else {
		fprintf(stderr, "Could not load the model, using a standard model instead.");
		model = Model();
	}

	return model;
}

//Load the model from an OBJ file: Using a path, scale, position and array of colours
Model ModelLoader::loadToVao_OBJ(const char* filePath, float scale, glm::vec3 position, std::vector<glm::vec3> colors) {
	Model model = loadToVao_OBJ(filePath, scale, scale, scale, position, colors);

	return model;
}

//Load the model from an OBJ file: Using a path, scale, position and a color
Model ModelLoader::loadToVao_OBJ(const char* filePath, float scale, glm::vec3 position, glm::vec3 color) {
	Model model = loadToVao_OBJ(filePath, scale, scale, scale, position, color);

	return model;
}

//Load the model from an OBJ file: Using a path, position and array of colours
Model ModelLoader::loadToVao_OBJ(const char* filePath, glm::vec3 position, glm::vec3 color) {
	Model model = loadToVao_OBJ(filePath, 1.0f, position, color);

	return model;
}

//Load the model from an OBJ file: Using a path and a position
Model ModelLoader::loadToVao_OBJ(const char* filePath, glm::vec3 position) {
	Model model = loadToVao_OBJ(filePath, 1.0f, position, glm::vec3(1, 0, 0));

	return model;
}

//Load a model file from an OBJ
Model ModelLoader::loadToVao_OBJ(const char* filePath) {
	Model model = loadToVao_OBJ(filePath, 1.0f, glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));

	return model;
}

/*
TEXTURED MODEL LOADER
*/

//Load a textured model from file and a texture with a given position and a default vertex colour array and a scale
Model ModelLoader::loadToVao_OBJ_Textured(const char* filePath, const char* imagePath, float scaleX, float scaleY, float scaleZ,
glm::vec3 position, std::vector<glm::vec3> colors) {

	//Arrays for the information
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	TextureLoader textureLoader = TextureLoader();

	//Load the Model
	if (loadOBJ(filePath, vertices, uvs, normals, UV_INVERT_Y)) {

		//Load a model file
		Model model = loadToVao(vertices, scaleX, scaleY, scaleZ, position, colors);

		//Load the texture
		GLuint textureID = textureLoader.loadBMP_custom(imagePath);

		//Create the textured model from the model, uvs and texture
		model.texture(uvs, textureID);

		//Add the normals to the model
		if (normals.size() > 0) {
			GLfloat* normalsTemp = &normals[0].x;
			int normalsSize = normals.size() * 3 * sizeof(GLfloat);
			model.setNormalsVboID(storeData(3, normalsTemp, normalsSize));
		}

		return model;
	}
	else {
		fprintf(stderr, "Could not load the model, using a standard model instead.");
		Model model = Model();
	return model;
}
}

//Load a textured model from file and a texture with a given position and a default vertex colour and a scale.
Model ModelLoader::loadToVao_OBJ_Textured(const char* filePath, const char* imagePath, float scaleX, float scaleY,
float scaleZ, glm::vec3 position, glm::vec3 color) {

	//Arrays for the information
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	TextureLoader textureLoader = TextureLoader();

	//Load the Model
	if (loadOBJ(filePath, vertices, uvs, normals, UV_INVERT_Y)) {

		//Load a model file
		Model model = loadToVao(vertices, scaleX, scaleY, scaleZ, position, color);

		//Load the texture
		GLuint textureID = textureLoader.loadBMP_custom(imagePath);

		//Create the textured model from the model, uvs and texture
		model.texture(uvs, textureID);

		//Add the normals to the model
		if (normals.size() > 0) {
			GLfloat* normalsTemp = &normals[0].x;
			int normalsSize = normals.size() * 3 * sizeof(GLfloat);
			model.setNormalsVboID(storeData(3, normalsTemp, normalsSize));
		}

		return model;
	}
	else {
		fprintf(stderr, "Could not load the model, using a standard model instead.");
		Model model = Model();
		return model;
	}
}

//Load a textured model from file and a texture with a given position and a default vertex colour array and a scale
Model ModelLoader::loadToVao_OBJ_Textured(const char* filePath, const char* imagePath, float scale, glm::vec3 position,
	std::vector<glm::vec3> colors) {
	Model model = loadToVao_OBJ_Textured(filePath, imagePath, scale, scale, scale, position, colors);

	return model;
}

//Load a textured model from file and a texture with a given position and a default vertex colour and a scale.
Model ModelLoader::loadToVao_OBJ_Textured(const char* filePath, const char* imagePath, float scale, glm::vec3 position,
	glm::vec3 color) {
	Model model = loadToVao_OBJ_Textured(filePath, imagePath, scale, scale, scale, position, color);

	return model;
}

//Load a textured model from file and a texture with a given position and a default vertex colour
Model ModelLoader::loadToVao_OBJ_Textured(const char* filePath, const char* imagePath, glm::vec3 position,
	glm::vec3 color) {
	Model model = loadToVao_OBJ_Textured(filePath, imagePath, 1.0f, position, color);
	return model;
}

//Load a textured model from file and a texture with a given position
Model ModelLoader::loadToVao_OBJ_Textured(const char* filePath, const char* imagePath, glm::vec3 position) {
	Model model = loadToVao_OBJ_Textured(filePath, imagePath, 1.0f, position, glm::vec3(1, 0, 0));
	return model;
}

//Load a textured model from file and a texture
Model ModelLoader::loadToVao_OBJ_Textured(const char* filePath, const char* imagePath) {
	Model model = loadToVao_OBJ_Textured(filePath, imagePath, 1.0f, glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
	return model;
}

/*
OTHER
*/

//OBJ Parser to retrieve the vertices, uvs and normals
bool ModelLoader::loadOBJ(const char *path, std::vector<glm::vec3> &vertices,
	std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, const unsigned int flags) {

	//Boolean values for flags
	bool uvInvertY = false;

	//Bitmasking checks
	if ((flags & NORMAL_LOADING) == NORMAL_LOADING) {
	}
	else if ((flags & UV_INVERT_Y) == UV_INVERT_Y) {
		uvInvertY = true;
	}

	//Create the temp arrays
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec2> temp_uvs;
	std::vector<unsigned int> verticesIndex;
	std::vector<unsigned int> normalsIndex;
	std::vector<unsigned int> uvsIndex;

	//Open the file
	std::ifstream stream = std::ifstream();
	stream.open(path);

	//Check if stream is open
	if (stream.is_open()) {
		//Read each of the lines
		std::string line = "";
		while (std::getline(stream, line)) {
			//Split the line around the spaces
			std::vector<std::string> words = StringUtils::split(line, ' ');

			//Check the first word as the identifier
			if (words[0].compare("#") == 0) {
				//This is a comment so ignore
			}
			else if (words[0].compare("v") == 0) {

				//This is a vector so create the different coordinates
				glm::vec3 vertex = glm::vec3();
				float x;
				float y;
				float z;

				//Check if the size of the line is big enough to accomodate the floats
				if (words.size() == 4) {

					//Parse the strings into floats
					x = stof(words[1]);
					y = stof(words[2]);
					z = stof(words[3]);

					//Add the vertex to the array
					vertex = glm::vec3(x, y, z);
					temp_vertices.insert(temp_vertices.end(), vertex);
				}
				else {
					fprintf(stderr, "A vertex in %s could not be parsed as it does not contain all the required elements\n", path);
					return false;
				}
			}
			else if (words[0].compare("vt") == 0) {
				//This is a UV coordinate
				glm::vec2 uv = glm::vec2();
				float x;
				float y;

				//Check if the size of the line is big enough to accomodate the floats
				if (words.size() == 3) {
					//Parse the strings into floats
					x = stof(words[1]);
					y = stof(words[2]);

					//Invert the y if the bitmask is set
					if (uvInvertY) {
						y = -y;
					}

					//Add the vertex to the array
					uv = glm::vec2(x, y);
					temp_uvs.insert(temp_uvs.end(), uv);
				}
				else {
					fprintf(stderr, "A UV in %s could not be parsed as it does not contain all the required elements\n", path);
					return false;
				}
			}
			else if (words[0].compare("vn") == 0) {
				//This is a normal so create the different coordinates
				glm::vec3 normal = glm::vec3();
				float x;
				float y;
				float z;

				//Check if the size of the line is big enough to accomodate the floats
				if (words.size() == 4) {
					//Parse the strings into floats
					x = stof(words[1]);
					y = stof(words[2]);
					z = stof(words[3]);

					//Add the vertex to the array
					normal = glm::vec3(x, y, z);
					temp_normals.insert(temp_normals.end(), normal);
				}
				else {
					fprintf(stderr, "A normal in %s could not be parsed as it does not contain all the required elements\n", path);
					return false;
				}
			}
			else if (words[0].compare("f") == 0) {
				//This is a face so create the different variables
				unsigned int vertexID[3];
				unsigned int uvID[3];
				unsigned int normalID[3];

				//Check if the size of the line is big enough to accomodate the floats
				if (words.size() == 4) {

					//Split each face vertex into its components
					for (int i = 0; i < 3; i++)
					{
						std::vector<std::string> components = StringUtils::split(words[i + 1], '/');

						//Parse each component and add it to the array
						if (components[0].compare("") != 0) {
							vertexID[i] = stoi(components[0]);
							verticesIndex.insert(verticesIndex.end(), vertexID[i]);
						}
						if (components[1].compare("") != 0) {
							uvID[i] = stoi(components[1]);
							uvsIndex.insert(uvsIndex.end(), uvID[i]);
						}
						if (components[2].compare("") != 0) {
							normalID[i] = stoi(components[2]);
							normalsIndex.insert(normalsIndex.end(), normalID[i]);
						}
					}
				}
				else {
					fprintf(stderr, "A face in %s could not be parsed as it does not contain all the required elements\n", path);
					return false;
				}
			}
		}

		//Convert the faces into the vertices, normals and uvs
		for (int i = 0; i < verticesIndex.size(); i++) {

			//Get the indices of its attributes
			if (verticesIndex.size() > 0) {
				unsigned int vertexIndex = verticesIndex[i];
				glm::vec3 vertex = temp_vertices[vertexIndex - 1];
				vertices.push_back(vertex);
			}
			if (uvsIndex.size() > 0) {
				unsigned int uvIndex = uvsIndex[i];
				glm::vec2 uv = temp_uvs[uvIndex - 1];
				uvs.push_back(uv);
			}
			if (normalsIndex.size() > 0) {
				unsigned int normalIndex = normalsIndex[i];
				glm::vec3 normal = temp_normals[normalIndex - 1];
				normals.push_back(normal);
			}
		}

		//Close the stream
		stream.close();
	}
	else {
		fprintf(stderr, "Could not open the OBJ file %s\n", path);
		return false;
	}

	return true;
}

//Create a new vao
GLuint ModelLoader::createVao() {
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	return vaoID;
}

//Store data inside a vao
GLuint ModelLoader::storeData(int attributeNumber, GLfloat data[], int size) {
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vertexBuffer;
}

//Bind the vao
void ModelLoader::bindVao(GLuint vaoID) {
	glBindVertexArray(vaoID);
}

//Unbind the vao
void ModelLoader::unbindVao() {
	glBindVertexArray(0);
}

//Basic model loading from plain vertices
//Returns the model data in a vector array
std::vector<glm::vec3> ModelLoader::getModelData(const int modelType) {
	std::vector<glm::vec3> vertices;

	//Get the correct models data
	switch (modelType) {
		//Load from the correct files
	case ModelLoader::MODEL_CUBE:
		vertices = loadModelFromFile("models/cube.model");
		break;
	case ModelLoader::MODEL_SQUARE:
		vertices = loadModelFromFile("models/square.model");
		break;
	case ModelLoader::MODEL_TRIANGLE:
		vertices = loadModelFromFile("models/triangle.model");
		break;
	default:
		fprintf(stderr, "Could not load the model specified, using cube model instead");
		vertices = loadModelFromFile("models/cube.model");
	}

	return vertices;
}

//Load the Model from a file
std::vector<glm::vec3> ModelLoader::loadModelFromFile(const char* filePath) {
	//Create the array
	std::vector<glm::vec3> vertices = std::vector<glm::vec3>();

	//Create the stream for the file
	std::ifstream in;
	in.open(filePath);

	float x;
	float y;
	float z;

	//Read the file
	if (in.is_open()) {
		while (!in.eof()) {
			in >> x >> y >> z;
			vertices.insert(vertices.end(), glm::vec3(x, y, z));
		}
		in.close();
	}
	else {
		fprintf(stderr, "Could not open the model %s", filePath);
	}

	return vertices;
}
