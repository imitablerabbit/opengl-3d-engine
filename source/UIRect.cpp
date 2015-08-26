#include "UIRect.h"

UIRect::UIRect() {
	//Set up the UIRect
	init(0.3f, 0.3f, glm::vec2(0, 0));
}

UIRect::UIRect(float scale, glm::vec2 position) {
	//Scale the position given so that the object will be at the proper position
	init(scale, scale, position);
}

UIRect::UIRect(float scaleX, float scaleY, glm::vec2 position) {
	//Scale the position given so that the object will be at the proper position
	init(scaleX, scaleY, position);
}

UIRect::~UIRect()
{
}

void UIRect::init(float scaleX, float scaleY, glm::vec2 position) {
	//Set the UI variables
	setPosition(position);

	//Set the model as the square
	ModelLoader loader = ModelLoader();
	model = loader.loadToVao(ModelLoader::MODEL_SQUARE);

	//Set the scale as a quater of the screen
	model.setScaleX(scaleX);
	model.setScaleY(scaleY);

	//Set the position of the model as the middle
	model.setPosition(glm::vec3(normalisePosition(), 0));

	//Create the model matrix
	resetModelMatrix();
}

/*
VIRTUAL OVERLOADS
*/

void UIRect::run() {
	//fprintf(stderr, "I am a UIRect");
}