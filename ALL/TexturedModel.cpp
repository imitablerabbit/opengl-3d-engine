#include "TexturedModel.h"

#include "ModelLoader.h"

TexturedModel::TexturedModel(Model model, std::vector<glm::vec2> uvs, GLuint textureID) {
	this->setVaoID(model.getVaoID());
	this->setVerticesVboID(model.getVerticesVboID());
	this->setVertexCount(model.getVertexCount());
	this->setScale(model.getScale());
	this->setPosition(model.getPosition());

	this->setTextured(true);

	ModelLoader modelLoader = ModelLoader();
	GLfloat *uvsTemp = &uvs[0].x;
	int uvsSize = uvs.size() * 2 * sizeof(GLfloat);

	this->uvVboID = modelLoader.storeData(2, uvsTemp, uvsSize);

	this->setColor(false);
	this->setColorsVboID(model.getColorsVboID());
}

TexturedModel::TexturedModel(Model model) {
	this->setVaoID(model.getVaoID());
	this->setVerticesVboID(model.getVerticesVboID());
	this->setVertexCount(model.getVertexCount());
	this->setScale(model.getScale());
	this->setPosition(model.getPosition());

	this->setTextured(false);
	this->uvVboID;

	this->setColor(true);
	this->setColorsVboID(model.getColorsVboID());
}

TexturedModel::~TexturedModel()
{
}


