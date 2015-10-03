#include "UIElement.h"

UIElement::UIElement()
{
}

UIElement::~UIElement()
{
}

/*
VIRTUAL FUNCTIONS
*/

//Run the UIElement
void UIElement::run(){
	//fprintf(stderr, "I am a UIElement");
}

/*
GETTERS AND SETTERS
*/

//This will return the model
Model UIElement::getModel() {
	return this->model;
}

//This will return the modelMatrix
glm::mat4 UIElement::getModelMatrix() {
	return this->modelMatrix;
}

//This will return the normalised position of the shape
glm::vec2 UIElement::getPosition() {
	return this->position;
}

//This will set the modelMatrix of the shape
void UIElement::setModelMatrix(const glm::mat4* modelMatrix) {
	this->modelMatrix = *modelMatrix;
}

//This will set the position of the shape (normalised)
void UIElement::setPosition(glm::vec2 position) {
	this->position = position;
}

//This will set the model for the UI
void UIElement::setModel(Model model) {
	this->model = model;
}

//This will set the color of the UI if it is not textured
void UIElement::setColor(glm::vec3 color) {
	model.setColor(color);
}

//This will set the alignment of the shape
void UIElement::setAlignment(const unsigned int alignment) {
	this->alignment = alignment;

	//Reset the position of the UI to reflect the change
	resetOffsets();
	model.setPosition(glm::vec3(normalisePosition(), 0));
	resetModelMatrix();
}

/*
UTIL FUNCTIONS
*/

//This will texture the UIElement
void UIElement::texture(GLuint textureID) {

	//Create the UVs
	std::vector<glm::vec2> uvs = std::vector<glm::vec2>();
	uvs.insert(uvs.end(), glm::vec2(1.0, 0));
	uvs.insert(uvs.end(), glm::vec2(0, 0));
	uvs.insert(uvs.end(), glm::vec2(0, 1.0));
	uvs.insert(uvs.end(), glm::vec2(0, 1.0));
	uvs.insert(uvs.end(), glm::vec2(1.0, 1.0));
	uvs.insert(uvs.end(), glm::vec2(1.0, 0));

	//Flip the uv coordinates if using DDS
	for (int i = 0; i < uvs.size(); i++) {
		uvs[i].y = -uvs[i].y;
	}

	//Texture the Model
	model.texture(uvs, textureID);
}

//Reset the Offsets for the alignments
void UIElement::resetOffsets() {
	if (alignment == ALIGN_CENTER) {
		xOffset = 0;
		yOffset = 0;
	}
	else if (alignment == ALIGN_TOP_LEFT) {
		xOffset = 1;
		yOffset = -1;
	}
	else if (alignment == ALIGN_TOP_RIGHT) {
		xOffset = -1;
		yOffset = -1;
	}
	else if (alignment == ALIGN_BOTTOM_LEFT) {
		xOffset = 1;
		yOffset = 1;
	}
	else if (alignment == ALIGN_BOTTOM_RIGHT) {
		xOffset = -1;
		yOffset = 1;
	}
}

//Resets the model matrix so that the shape can be moved each frame easier
void UIElement::resetModelMatrix() {
	//Create the modelMatrix from scratch
	modelMatrix = glm::mat4();
	modelMatrix = glm::scale(modelMatrix, glm::vec3(model.getScaleX(), model.getScaleY(), 0));
	modelMatrix = glm::translate(modelMatrix, model.getPosition());
}

//This will normalise the position and align it in order to change the model position
glm::vec2 UIElement::normalisePosition() {
	//Scale the position variables to add to the model position
	glm::vec2 position = this->getPosition();
	position.x = (position.x / model.getScaleX()) + xOffset;
	position.y = (position.y / model.getScaleY()) + yOffset;

	return position;
}