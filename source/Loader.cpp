#include "Loader.h"

Loader::Loader() {
}

Loader::~Loader() {
}

//Load the data to a vao
Model Loader::loadToVao(GLfloat data[], int size, int vertexCount) {
	GLuint vaoID = createVao();
	bindVao(vaoID);
	GLuint vboID = storeData(0, data, size);
	unbindVao();
	return Model(vaoID, vboID, vertexCount);
}

//Overloaded function so that the function can take a vector of vec3's
Model Loader::loadToVao(std::vector<glm::vec3> data) {
	GLfloat *flat_array = &data[0].x;
	int size = data.size() * 3 * sizeof(GLfloat);
	int vertexCount = data.size();
	Model temp = loadToVao(flat_array, size, vertexCount);
	return temp;
}

//Create a new vao
GLuint Loader::createVao() {
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	return vaoID;
}

//Store data inside a vao
GLuint Loader::storeData(int attributeNumber, GLfloat data[], int size) {
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vertexBuffer;
}

//Bind the vao
void Loader::bindVao(GLuint vaoID) {
	glBindVertexArray(vaoID);
}

//Unbind the vao
void Loader::unbindVao() {
	glBindVertexArray(0);
}