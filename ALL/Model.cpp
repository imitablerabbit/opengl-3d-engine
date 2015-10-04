#include "Model.h"
#include "ModelLoader.h"

/*
Constructors and Destructors
*/

Model::Model(GLuint vaoID, GLuint verticesVboID, GLuint uvVboID, GLuint normalsVboID, GLuint colorsVboID, int vertexCount, float scaleX, float scaleY, float scaleZ,
	glm::vec3 position) {
	this->vaoID = vaoID;

	this->verticesVboID = verticesVboID;
	this->vertexCount = vertexCount;

	this->uvVboID = uvVboID;

	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;

	this->position = position;

	this->textured = false;
	this->colored = true;
	this->colorsVboID = colorsVboID;

	this->normalsVboID = normalsVboID;
	if (normalsVboID != 0) {
		this->normals = true;
	}

	this->material = Material();
}

Model::Model(GLuint vaoID, GLuint verticesVboID, GLuint uvVboID, GLuint colorsVboID, int vertexCount, float scaleX, float scaleY, float scaleZ,
	glm::vec3 position) {
	this->vaoID = vaoID;

	this->verticesVboID = verticesVboID;
	this->vertexCount = vertexCount;

	this->uvVboID = uvVboID;

	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;

	this->position = position;

	this->textured = false;
	this->colored = true;
	this->colorsVboID = colorsVboID;

	this->normals = true;

	this->material = Material();
}

Model::Model(GLuint vaoID, GLuint verticesVboID, GLuint colorsVboID, int vertexCount, float scaleX, float scaleY, float scaleZ,
	glm::vec3 position) {
	this->vaoID = vaoID;

	this->verticesVboID = verticesVboID;
	this->vertexCount = vertexCount;

	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;

	this->position = position;

	this->textured = false;
	this->colored = true;
	this->colorsVboID = colorsVboID;

	this->normals = true;

	this->material = Material();
}

Model::Model(GLuint vaoID, GLuint verticesVboID, GLuint colorsVboID, int vertexCount, float scale, glm::vec3 position) {
	this->vaoID = vaoID;

	this->verticesVboID = verticesVboID;
	this->vertexCount = vertexCount;

	this->scaleX = scale;
	this->scaleY = scale;
	this->scaleZ = scale;

	this->position = position;

	this->textured = false;
	this->colored = true;
	this->colorsVboID = colorsVboID;

	this->normals = true;

	this->material = Material();
}

Model::Model() {
	ModelLoader loader = ModelLoader();
	Model model = loader.loadToVao(ModelLoader::MODEL_CUBE);
	this->vaoID = model.getVaoID();

	this->verticesVboID = model.getVerticesVboID();
	this->vertexCount = model.getVertexCount();

	this->scaleX = model.getScaleX();
	this->scaleY = model.getScaleY();
	this->scaleZ = model.getScaleZ();

	this->position = model.getPosition();

	this->textured = model.isTextured();
	this->colored = model.hasColor();
	this->colorsVboID = model.getColorsVboID();

	this->normals = model.hasNormals();
	this->material = Material();
}

Model::~Model() {
}

/*
Util functions
*/

//APPLYING A TEXTURE
//This will apply a texture to the model
void Model::texture(std::vector<glm::vec2> uvs, GLuint textureID) {
	ModelLoader modelLoader = ModelLoader();

	//Make sure that the function has the uvs
	if (uvs.size() > 0) {
		GLfloat *uvsTemp = &uvs[0].x;
		int uvsSize = uvs.size() * 2 * sizeof(GLfloat);

		this->uvVboID = modelLoader.storeData(2, uvsTemp, uvsSize);
		this->textureID = textureID;

		setIsTextured(true);
	}
	else {
		fprintf(stderr, "Model does not currently have UV coordinates");
	}
}

//Set the models texture to a texture which has already been generated
void Model::texture(GLuint textureID) {
	//Make sure that the model already has a uv vbo id
	if (this->uvVboID != 0) {
		setIsTextured(true);
		this->textureID = textureID;
	}
	else {
		fprintf(stderr, "Model does not currently have UV coordinates");
	}
}

//This will remove the texture from the model
void Model::removeTexture() {
	setTextureID(0);
	setIsTextured(false);
}

//Translation functions
//Translate via a vector
void Model::translate(glm::vec3 translation) {
	position += translation;
}

//Translate x axis
void Model::translateX(float xTranslation) {
	translate(glm::vec3(xTranslation, 0, 0));
}

//Translate y axis
void Model::translateY(float yTranslation) {
	translate(glm::vec3(0, yTranslation, 0));
}

//Translate z axis
void Model::translateZ(float zTranslation) {
	translate(glm::vec3(0, 0, zTranslation));
}

//Create the modelMatrix
glm::mat4 Model::createModelMatrix() {

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	//Apply the transformations to the matrix
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleX, scaleY, scaleZ));
	modelMatrix = glm::translate(modelMatrix, position);

	return modelMatrix;
}

/*
Getters and Setters
*/

//GETTERS
//Return the vaoID
GLuint Model::getVaoID() {
	return this->vaoID;
}

//Return the positions vboID
GLuint Model::getVerticesVboID() {
	return this->verticesVboID;
}

//Return the colors vboID
GLuint Model::getColorsVboID() {
	return this->colorsVboID;
}

//Return the uvs vboID
GLuint Model::getUVsVboID() {
	return this->uvVboID;
}

//Return the texture ID
GLuint Model::getTextureID() {
	return this->textureID;
}

//Returns the normals vbo ID
GLuint Model::getNormalsVboID() {
	return this->normalsVboID;
}

//Return the number of verticies
int Model::getVertexCount() {
	return this->vertexCount;
}

//Return the scale of the object
float Model::getScale() {
	return this->scaleX;
}

//Return the scale of the object
float Model::getScaleX() {
	return this->scaleX;
}

//Return the scale of the object
float Model::getScaleY() {
	return this->scaleY;
}

//Return the scale of the object
float Model::getScaleZ() {
	return this->scaleZ;
}

//Return the postion of the model
glm::vec3 Model::getPosition() {
	return this->position;
}

//Return the material of the model
Material Model::getMaterial() {
	return this->material;
}

//Return the reflectivity of the model
float Model::getReflectivity() {
	return this->material.getReflectivity();
}

//Return the dampening
float Model::getDampening() {
	return this->material.getDampening();
}

//SETTERS
//Set the vaoID
void Model::setVaoID(GLuint vaoID) {
	this->vaoID = vaoID;
}

//Set the positions vboID
void Model::setVerticesVboID(GLuint verticesVboID) {
	this->verticesVboID = verticesVboID;
}

//Set the colors vboID
void Model::setColorsVboID(GLuint colorsVboID) {
	this->colorsVboID = colorsVboID;
}

//Set the UV Vbo ID
void Model::setUVsVboID(GLuint uvVboID) {
	this->uvVboID = uvVboID;
}

//Set the texture ID
void Model::setTextureID(GLuint textureID) {
	this->textureID = textureID;
}

//Set the normals Vbo ID
void Model::setNormalsVboID(GLuint normalsVboID) {
	this->normalsVboID = normalsVboID;
}

//Set the number of verticies
void Model::setVertexCount(int vertexCount) {
	this->vertexCount = vertexCount;
}

//Set the scale of the object
void Model::setScale(float scale) {
	this->scaleX = scale;
	this->scaleY = scale;
	this->scaleZ = scale;
}

//Set the scale of the object
void Model::setScaleX(float scale) {
	this->scaleX = scale;
}

//Set the scale of the object
void Model::setScaleY(float scale) {
	this->scaleY = scale;
}

//Set the scale of the object
void Model::setScaleZ(float scale) {
	this->scaleZ = scale;
}

//Set the postion of the model
void Model::setPosition(glm::vec3 position) {
	this->position = position;
}

//Set the color of the model
void Model::setColor(glm::vec3 color) {
	std::vector<glm::vec3> colors = std::vector<glm::vec3>();
	for (int i = 0; i < getVertexCount(); i++) {
		colors.insert(colors.end(), color);
	}

	GLfloat *colorsTemp = &colors[0].x;
	int colorsSize = colors.size() * 3 * sizeof(GLfloat);

	ModelLoader loader = ModelLoader();
	GLuint colorsID = loader.storeData(1, colorsTemp, colorsSize);

	this->colorsVboID = colorsID;

	setHasColor(true);
}

//Set the Material of the model
void Model::setMaterial(Material material) {
	this->material = material;
}

//Set the reflectivity of the model
void Model::setReflectivity(float reflectivity) {
	this->material.setReflectivity(reflectivity);
}

//Set the dampening
void Model::setDampening(float dampening) {
	this->material.setDampening(dampening);
}

/*
OTHER UTIL FUNCTIONS
*/

//Set whether the model is colored
void Model::setHasColor(bool colored) {
	this->colored = colored;
}

//Set whether the model is textured
void Model::setIsTextured(bool textured) {
	this->textured = textured;
}

//Sets whether the model has normals
void Model::setHasNormals(bool normals) {
	this->normals = normals;
}

//Returns whether the model is colored
GLint Model::hasColor() {
	return this->colored;
}

//Returns whether the model is textured
GLint Model::isTextured() {
	return this->textured;
}

//Returns whether the models has normals
GLint Model::hasNormals() {
	return this->normals;
}